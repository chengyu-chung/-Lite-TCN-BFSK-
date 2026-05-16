/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 井下通信系统 - 井上主控站 (Ground Node, V7 INT8)
  * @note           :
  * 1) AI 模型为 INT8 量化 TCN，输入 960 点，输出 boundary/frame 两路序列。
  * 2) 协议为 32bit：sync(8)+dest(4)+src(4)+payload(16)，同步头固定 0xB6。
  * 3) 载荷定义为 payload16=[temp8|pres8]；保留下行命令帧发送接口。
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>  
#include <stdio.h>         
#include <math.h>
// 仅允许使用 CMSIS-DSP，未启用时直接报错
#ifndef USE_CMSIS_DSP
  #error "CMSIS-DSP not enabled: please define USE_CMSIS_DSP=1 in project macros."
#endif
#ifndef ARM_MATH_CM4
#define ARM_MATH_CM4
#endif
#include "arm_math.h"
#include "ad9833.h"        
#include "network_1.h"       
#include "network_1_data.h"  
#include "relay_control.h" 
#include "test_sample_frame.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    STATE_LISTENING,   // 监听态：等待井下回传
    STATE_INFERENCING, // 推理态：执行 AI 解调
    STATE_TRANSMITTING // 发送态：下发控制指令
} SystemState_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 井上节点主要是被动接收和主动下发，不需要自动循环定时器
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
SystemState_t current_state = STATE_LISTENING; 

// 记录串口命令（主循环执行）
uint8_t pending_cmd = 0;
static uint8_t replay_once = 0;

// 核心控制实例化
volatile AI_Demod_Ctrl_t demodCtrl = {0}; 
volatile Modulate_Ctrl_t modCtrl = {0};   

uint16_t adc_dma_buffer[FRAME_SAMPLES];   
AI_ALIGNED(4) static ai_u8 activations[AI_NETWORK_1_DATA_ACTIVATIONS_SIZE]; 
static ai_handle network = AI_HANDLE_NULL; 

// INT8 量化输入/输出缓冲区
int8_t ai_in_buffer[FRAME_SAMPLES];
int8_t ai_out_boundary[AI_NETWORK_1_OUT_1_SIZE];
int8_t ai_out_frame[AI_NETWORK_1_OUT_2_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ====================================================================
// AI 量化与后处理参数（必须与当前 X-CUBE-AI 生成模型严格一致）
// 说明：
// - AI_INPUT_SCALE / AI_INPUT_ZP 来自 network_1.c 的 input intq
// - AI_FRAME_ZP 来自 frame 输出张量 intq（用于 bit 判决阈值）
// - 这些参数更新后，Ground/Underground 需保持一致
// ====================================================================
#define AI_INPUT_SCALE        (0.04223548248410225f) // input scale
#define AI_INPUT_ZP           (3)                    // input zero-point
#define AI_NORM_EPS           (1.0e-5f)              // z-norm 防除零
#define AI_FRAME_ZP           (-14)                  // frame 输出零点（bit判决基准）
#define AI_STRIDE             (3)                    // 前端池化步长
#define AI_LATENT_SAMPLES     (256)                  // 32bit*24/3
#define AI_LATENT_SPB         (8)                    // 24/3
#define AI_BOUNDARY_TOP_K     (3)                    // 边界候选数
#define AI_BOUNDARY_AMBIGUOUS_THRESHOLD  (4)         // Top1/Top2 模糊阈值
#define INFER_TIMEOUT_MS      (300)                  // 推理超时保护
#define SYNC_MAX_ERR          (0)                    // 同步头最大允许错误位数
#define SYNC_SHIFT_RANGE      (8)                    // 起点细修搜索范围：[-4,+4]
#define AI_REPLAY_MODE        (1)                    // 0: 实采样  1: 回放测试

static float32_t adc_f32_buf[FRAME_SAMPLES];

// ====================================================================
// AI 帧输出判决函数（工业化稳健版）
// 说明：
// - 对每 bit 的 8 个 latent 采样点做加权积分，抑制单点噪声和相位抖动。
// - 判决阈值在量化域与 zero-point 对齐，避免浮点反量化开销。
// ====================================================================
static inline uint8_t DecodeFrameBitWeighted(const int8_t* frame, int base)
{
    // 权重窗口: [1,2,2,2,2,2,2,1]，总权重 14
    int32_t acc = 0;
    acc += 1 * frame[base + 0];
    acc += 2 * frame[base + 1];
    acc += 2 * frame[base + 2];
    acc += 2 * frame[base + 3];
    acc += 2 * frame[base + 4];
    acc += 2 * frame[base + 5];
    acc += 2 * frame[base + 6];
    acc += 1 * frame[base + 7];

    const int32_t th = 14 * (int32_t)AI_FRAME_ZP;
    return (acc > th) ? 1U : 0U;
}

// ====================================================================
// 串口打印重定向（用于上位机显示）
// ====================================================================
int fputc(int ch, FILE *f) {
    extern UART_HandleTypeDef huart2; 
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/**
  * @brief  下行指令帧组包（地面端 -> 井下端）
  */
void BuildTxFrame(uint8_t destAddr, uint8_t srcAddr, uint32_t payloadData) {
    // 32bit 短帧：sync(8)=0xB6 | dest(4) | src(4) | payload(16)
    uint16_t payload16 = (uint16_t)(payloadData & 0xFFFF);
    modCtrl.txFrame = 0U;
    modCtrl.txFrame |= ((uint32_t)0xB6U << 24);
    modCtrl.txFrame |= (((uint32_t)destAddr & 0x0FU) << 20);
    modCtrl.txFrame |= (((uint32_t)srcAddr  & 0x0FU) << 16);
    modCtrl.txFrame |= (uint32_t)payload16;
}

// 下行指令触发接口（可在串口接收中断中调用）
void Send_Command_To_Underground(uint8_t cmd) {
    // 仅允许在监听态发命令，避免打断推理流程
    if (current_state != STATE_LISTENING) {
        return;
    }
    // 若当前仍在发送上一帧，则直接丢弃本次请求，避免重入
    if (modCtrl.isTransmitting) {
        return;
    }

    BuildTxFrame(ADDR_UNDERGROUND, LOCAL_ADDRESS, (uint32_t)cmd);

    // 打印组包结果：地址、命令、32bit帧内容（便于串口联调）
    printf("[TX] build frame: dest=0x%X src=0x%X cmd=0x%02X payload=0x%04X frame=0x%08lX\r\n",
           ADDR_UNDERGROUND, LOCAL_ADDRESS, cmd, (unsigned int)cmd, (unsigned long)modCtrl.txFrame);

    HAL_ADC_Stop_DMA(&hadc1); 
    demodCtrl.adcReadyFlag = 0;
    RXrelayOff(); TXrelayOn(); APon(); HAL_Delay(15); 
    modCtrl.txBitIndex = 0;     
    modCtrl.isTransmitting = 1; 
    HAL_TIM_Base_Start_IT(&htim3); 
    current_state = STATE_TRANSMITTING;
    printf("[Current State] state=%d \r\n",
           current_state);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  __disable_irq(); 
  
  AD9833_Init();
  AD9833_SetFreq(100, 0); 
  AD9833_SetFreq(200, 1); 
  AD9833_SelectFreq(0);   

  // ======================= AI Runtime 初始化 =======================
  // 1) 创建网络实例
  // 2) 绑定权重区与激活区
  // 3) 初始化网络，失败则进入 Error_Handler
  ai_error ai_err = ai_network_1_create(&network, AI_NETWORK_1_DATA_CONFIG);
  if (ai_err.type != AI_ERROR_NONE) {
      printf("[AI] create failed: type=%d code=%d\r\n", ai_err.type, ai_err.code);
      Error_Handler();
  }

  const ai_network_params ai_params = {
      AI_NETWORK_1_DATA_WEIGHTS(ai_network_1_data_weights_get()),
      AI_NETWORK_1_DATA_ACTIVATIONS(activations)
  };

  if (!ai_network_1_init(network, &ai_params)) {
      ai_err = ai_network_1_get_error(network);
      printf("[AI] init failed: type=%d code=%d\r\n", ai_err.type, ai_err.code);
      Error_Handler();
  }

  // 上电后仅提示“模型已就绪”，避免出现含糊加载中提示
  printf("[AI] model ready. INT8 network initialized.\r\n");

#if !AI_REPLAY_MODE
  HAL_TIM_Base_Start(&htim2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
#endif

  // 中断优先级：ADC/DMA 高于 TIM3 发送
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
  
  __enable_irq(); 
  
  printf("Ground Node (Master) Initialized!\r\n");
  printf("[Current State] state=%d \r\n", current_state);

#if AI_REPLAY_MODE
  for (int i = 0; i < FRAME_SAMPLES && i < TEST_FRAME_INPUT_SAMPLES; i++) {
      adc_dma_buffer[i] = g_test_adc_frame[i];
  }

  demodCtrl.adcReadyFlag = 1;
  replay_once = 0;
  printf("[REPLAY] One-frame test loaded. SNR=%.1f dB, pad_pre=%d\r\n", (double)TEST_FRAME_SNR_DB, TEST_FRAME_PAD_PRE);
#endif

  // 启动串口单字节接收（命令索引：s1/s2/s3/s4/s5/s6）
  USART_StartReceive();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      
// 主循环巡逻：如果中断收到命令了，在这里安全地执行！
    if (pending_cmd != 0) {
       // printf("\r\n[Main] Safe to execute! Starting TX for command: 0x%X\r\n", pending_cmd);
        Send_Command_To_Underground(pending_cmd);
        pending_cmd = 0; // 执行完清空标志位
    }    
    switch (current_state) {
        case STATE_LISTENING:
            APoff(); TXrelayOff(); RXrelayOn();

#if AI_REPLAY_MODE
            if (!replay_once && demodCtrl.adcReadyFlag == 1) {
                demodCtrl.inferStartTick = HAL_GetTick();
                current_state = STATE_INFERENCING;
                printf("[Current State] state=%d \r\n", current_state);
            }
#else
            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.inferStartTick = HAL_GetTick();
                current_state = STATE_INFERENCING;
               // printf("[Current State] state=%d (INFERENCING)\r\n", current_state);
            }
#endif
            break;

        case STATE_INFERENCING:
        {
            // 推理超时保护：如果从 ADC 完成到推理完成超过一定时间（如 300ms），则强制重置回监听态，避免死锁
            if ((HAL_GetTick() - demodCtrl.inferStartTick) > INFER_TIMEOUT_MS) {
                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
                break;
            }

            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.adcReadyFlag = 0;

                // 1) 输入准备（统一路径）：ADC -> z-norm -> int8 量化
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    adc_f32_buf[i] = (float32_t)adc_dma_buffer[i];
                }

                float32_t mean_f = 0.0f;
                float32_t std_f = 1.0f;

                arm_mean_f32(adc_f32_buf, FRAME_SAMPLES, &mean_f);
                arm_std_f32(adc_f32_buf, FRAME_SAMPLES, &std_f);

                // 防止极端静态输入导致除零；仅做一次下限保护，避免重复缩放
                if (std_f < AI_NORM_EPS) {
                    std_f = AI_NORM_EPS;
                }
                const float32_t inv_std = 1.0f / std_f;
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    float32_t norm = (adc_f32_buf[i] - mean_f) * inv_std;
                    float32_t fq = (float32_t)(norm / AI_INPUT_SCALE);
                    int32_t q = (int32_t)(fq + (fq >= 0.0f ? 0.5f : -0.5f)) + (int32_t)AI_INPUT_ZP;
                    if (q > 127) q = 127;
                    if (q < -128) q = -128;
                    ai_in_buffer[i] = (int8_t)q;
                }

                // 2) AI 推理
                ai_buffer *ai_input = ai_network_1_inputs_get(network, NULL);
                ai_input[0].data = AI_HANDLE_PTR(ai_in_buffer);
                ai_buffer *ai_output = ai_network_1_outputs_get(network, NULL);
                ai_output[0].data = AI_HANDLE_PTR(ai_out_boundary);
                ai_output[1].data = AI_HANDLE_PTR(ai_out_frame);

                // 运行 AI 推理并检查返回批次数；异常时直接回监听态，避免状态机卡死
                ai_i32 n_batch = ai_network_1_run(network, ai_input, ai_output);
                if (n_batch != 1) {
                    ai_error run_err = ai_network_1_get_error(network);
                    printf("[AI] run failed: batch=%ld type=%d code=%d\r\n",
                           (long)n_batch, run_err.type, run_err.code);

#if !AI_REPLAY_MODE
                    HAL_ADC_Stop_DMA(&hadc1);
                    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
#endif
                   // demodCtrl.syncMatched = 0;
                    current_state = STATE_LISTENING;
                    break;
                }

                // 3) boundary Top-3 候选（仅后处理，不增加推理次数）
                int best_idx = 0;
                int8_t best_val = ai_out_boundary[0];
                int second_idx = 0;
                int8_t second_val = (int8_t)-128;
                int third_idx = 0;
                int8_t third_val = (int8_t)-128;
                
                // 从第 1 个元素开始遍历，找到 Top-3 最大值及其索引
                for (int i = 1; i < AI_NETWORK_1_OUT_1_SIZE; i++) {
                    int8_t v = ai_out_boundary[i];
                    if (v > best_val) {
                        third_val = second_val; third_idx = second_idx;
                        second_val = best_val; second_idx = best_idx;
                        best_val = v; best_idx = i;
                    } else if (v > second_val) {
                        third_val = second_val; third_idx = second_idx;
                        second_val = v; second_idx = i;
                    } else if (v > third_val) {
                        third_val = v; third_idx = i;
                    }
                }
                // 根据 Top-3 与模糊阈值确定候选起始索引数量（1 或 3），并进行同步头匹配验证
                int candidate_idxs[AI_BOUNDARY_TOP_K] = {best_idx, second_idx, third_idx};
                int candidate_count = 1;
                if ((best_val - second_val) <= AI_BOUNDARY_AMBIGUOUS_THRESHOLD) {
                    candidate_count = AI_BOUNDARY_TOP_K;
                }
                const uint8_t syncRef8 = 0xB6U; // 同步头 10110110
                uint8_t head_ok = 0;
                uint8_t best_head_err = 8; // 记录当前最佳候选的同步头错误位数

                // 4) 边界后处理：Top-K 候选 + 局部移位细修 + 同步头汉明距离判定
                int best_start = 0;
                uint8_t has_candidate = 0;
                // 联合评分：优先最小同步头错误，其次最大地址匹配分
                int best_addr_score = -1;

                for (int c = 0; c < candidate_count; c++) {
                    int center = candidate_idxs[c];

                    for (int delta = -SYNC_SHIFT_RANGE; delta <= SYNC_SHIFT_RANGE; delta++) {
                        int start = center + delta;
                        if (start < 0) start = 0;
                        if (start > (AI_NETWORK_1_OUT_2_SIZE - AI_LATENT_SAMPLES)) {
                            start = (AI_NETWORK_1_OUT_2_SIZE - AI_LATENT_SAMPLES);
                        }

                        // 无数组实现：边解前16bit，边统计head_err并组装地址
                        uint8_t head_err = 0;
                        uint8_t cand_dest = 0;
                        uint8_t cand_src = 0;

                        for (int bit = 0; bit < 16; bit++) {
                            int base = start + bit * AI_LATENT_SPB;
                            uint8_t hb = DecodeFrameBitWeighted(ai_out_frame, base) & 0x01U;

                            if (bit < 8) {
                                uint8_t refb = (uint8_t)((syncRef8 >> (7 - bit)) & 0x01U);
                                if (hb != refb) head_err++;
                            } else if (bit < 12) {
                                cand_dest = (uint8_t)((cand_dest << 1) | hb);
                            } else {
                                cand_src = (uint8_t)((cand_src << 1) | hb);
                            }
                        }

                        int addr_score = 0;
                        if (cand_dest == LOCAL_ADDRESS)    addr_score += 2; // 目标地址命中权重更高
                        if (cand_src  == ADDR_UNDERGROUND) addr_score += 1;

                        // 联合选优：先比 head_err，再比 addr_score
                        if (!has_candidate ||
                            (head_err < best_head_err) ||
                            (head_err == best_head_err && addr_score > best_addr_score)) {
                            has_candidate = 1;
                            best_head_err = head_err;
                            best_addr_score = addr_score;
                            best_start = start;
                        }
                    }
                }

                // 最优候选满足同步头阈值则通过
                if (has_candidate && best_head_err <= SYNC_MAX_ERR) {
                    head_ok = 1;
                }


                // 对外状态标记：供调试/监控查看最近一次同步头判定结果
               // demodCtrl.syncMatched = head_ok ? 1U : 0U;

                // 仅当同步头通过时，才对最佳起点解完整 32bit 帧（打包为 uint32_t）
                if (head_ok) {
                    uint32_t rf = 0U;
                    for (int bit = 0; bit < FRAME_BITS; bit++) {
                        int base = best_start + bit * AI_LATENT_SPB;
                        rf = (rf << 1) | (uint32_t)(DecodeFrameBitWeighted(ai_out_frame, base) & 0x01U);
                    }
                    demodCtrl.rxFrame = rf;
                }

                // 5) 业务解析与输出：同步头通过（容错判定）则解析地址和载荷，否则丢弃
                if (head_ok) {
                    demodCtrl.destAddr = (uint8_t)((demodCtrl.rxFrame >> 20) & 0x0FU);
                    demodCtrl.srcAddr  = (uint8_t)((demodCtrl.rxFrame >> 16) & 0x0FU);
                    demodCtrl.payloadData = (uint32_t)(demodCtrl.rxFrame & 0xFFFFU);

                    // 地址匹配成功才作为有效接收；否则按地址错误丢帧
                    if (demodCtrl.destAddr == LOCAL_ADDRESS) {
                        uint8_t t_u8 = (uint8_t)((demodCtrl.payloadData >> 8) & 0xFFU);
                        uint8_t p_u8 = (uint8_t)(demodCtrl.payloadData & 0xFFU);

                        printf("[RX] Node:0x%X -> Ground | payloadData=0x%04lX | Temp: %u | Pres: %u\r\n",
                               demodCtrl.srcAddr,
                               (unsigned long)demodCtrl.payloadData,
                               (unsigned int)t_u8,
                               (unsigned int)p_u8);

#if AI_REPLAY_MODE
                        int bit_err = 0;
                        for (int i = 0; i < FRAME_BITS; i++) {
                            uint8_t b_hat = (uint8_t)((demodCtrl.rxFrame >> (31 - i)) & 0x01U);
                            if (b_hat != g_test_bits_32[i]) bit_err++;
                        }
                        printf("[REPLAY] dest=0x%X src=0x%X payload=0x%04lX | bit_err=%d/%d\r\n",
                               demodCtrl.destAddr, demodCtrl.srcAddr, (unsigned long)demodCtrl.payloadData, bit_err, FRAME_BITS);
#endif
                    } else {
                        //printf("[RX-ERR] frame dropped: address mismatch (dest=0x%X, local=0x%X)\r\n",
                        //       demodCtrl.destAddr, LOCAL_ADDRESS);
                    }
                } else {
                    //printf("[RX-ERR] frame dropped: sync header mismatch (head_err=%u, th=%u)\r\n",
                    //       best_head_err, (uint8_t)SYNC_MAX_ERR);
                }
            }

            // 单帧推理完成后回到监听态（除非切换为下发状态）
#if AI_REPLAY_MODE
            if (!replay_once) {
                replay_once = 1;
            }
            current_state = STATE_LISTENING;
            printf("[Current State] state=%d \r\n", current_state);
#else
            HAL_ADC_Stop_DMA(&hadc1);
            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
            current_state = STATE_LISTENING;
#endif
            break;
        }

        case STATE_TRANSMITTING:
            if (modCtrl.isTransmitting == 0) {
                APoff(); TXrelayOff(); HAL_Delay(5); RXrelayOn();

                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
                printf("[TX] Command sent successfully.\r\n");
                printf("[Current State] state=%d \r\n",
                       current_state
                       );
            }
            break;
    }

    // 关闭主循环 while(1)
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1 && current_state == STATE_LISTENING) {
        demodCtrl.adcReadyFlag = 1; 
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        if (modCtrl.isTransmitting && modCtrl.txBitIndex >= 0 && modCtrl.txBitIndex < (FRAME_BITS + TAIL_BITS)) {
            
            if (modCtrl.txBitIndex < FRAME_BITS) {
                uint8_t bit = (uint8_t)((modCtrl.txFrame >> (31 - modCtrl.txBitIndex)) & 0x01U);
                if (bit == 1U) {
                    AD9833_SelectFreq(1);
                } else {
                    AD9833_SelectFreq(0);
                }
            }
            else {
                AD9833_SelectFreq(0);
            }
            
            modCtrl.txBitIndex++; 
            if (modCtrl.txBitIndex >= (FRAME_BITS + TAIL_BITS)) {
                modCtrl.txBitIndex = -1; modCtrl.isTransmitting = 0;    
                HAL_TIM_Base_Stop_IT(&htim3);  
            }
        }
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
