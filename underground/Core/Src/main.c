/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 井下通信终端主程序 (Downhole Node, V7 INT8)
  * @note           :
  * 1) AI 模型为 INT8 量化 TCN，输入 960 点，输出 boundary/frame 两路序列。
  * 2) 协议为 32bit：sync(8)+dest(4)+src(4)+payload(16)，同步头固定 0xB6。
  * 3) 井下收到命令后回传 payload16=[temp8|pres8]，并保留硬件扫频命令入口。
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
// CMSIS-DSP 需要在包含 arm_math.h 前声明目标内核
// STM32L476 = Cortex-M4F
#ifndef ARM_MATH_CM4
#define ARM_MATH_CM4
#endif
#include "arm_math.h"
#include "ad9833.h"        
#include "network.h"       
#include "network_data.h"  
#include "relay_control.h" 

// 引入数字温度传感器驱动
#include "ds18b20.h"  
#include "test_sample_frame.h"
// #include "flash_l4.h" // 预留的 Flash 驱动头文件接口
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// --- 核心三段式状态机 ---
typedef enum {
    STATE_LISTENING,   // [状态] 监听总线，并执行异步倒计时
    STATE_INFERENCING, // [状态] 执行 AI 解调，或直接处理回传任务
    STATE_TRANSMITTING // [状态] 物理层回传 (含 4-bit 尾随保护)
} SystemState_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// TAIL_BITS 已在 main.h 统一定义（与 Ground 保持一致）
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// --- 系统控制与状态机 ---
SystemState_t current_state = STATE_LISTENING;

// --- 核心控制器实例化 ---
volatile AI_Demod_Ctrl_t demodCtrl = {0};
volatile Modulate_Ctrl_t modCtrl = {0};

// --- ADC 与 AI 缓冲区（尺寸与模型输入/输出定义绑定）---
uint16_t adc_dma_buffer[FRAME_SAMPLES];
AI_ALIGNED(4) static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
static ai_handle network = AI_HANDLE_NULL;

int8_t ai_in_buffer[FRAME_SAMPLES];
int8_t ai_out_boundary[AI_NETWORK_OUT_1_SIZE];
int8_t ai_out_frame[AI_NETWORK_OUT_2_SIZE];

// --- 井下专属运行参数 ---
uint8_t  is_continuous_mode = 0;
uint32_t last_tx_timestamp = 0;
uint8_t  real_temperature = 25;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


// ====================================================================
// 串口打印重定向（用于上位机显示）
// ====================================================================
int fputc(int ch, FILE *f) {
    extern UART_HandleTypeDef huart2; // 假设你用的是 USART2
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
    return ch;
}

/**
  * @brief  下行/上行统一组帧（V7: 32bit）
  * @note   帧结构：sync(8)+dest(4)+src(4)+payload(16)
  */
void BuildTxFrame(uint8_t destAddr, uint8_t srcAddr, uint32_t payloadData) {
    uint32_t sync = 0xB6U;
    uint32_t d = ((uint32_t)destAddr & 0x0FU);
    uint32_t s = ((uint32_t)srcAddr & 0x0FU);
    uint32_t p16 = ((uint32_t)payloadData & 0xFFFFU);
    modCtrl.txFrame = (sync << 24) | (d << 20) | (s << 16) | p16;
}

// ====================================================================
// AI 量化与后处理参数（必须与当前 X-CUBE-AI 生成模型严格一致）
// 说明：
// - AI_INPUT_SCALE / AI_INPUT_ZP 来自 network.c 的 input intq 声明
// - AI_FRAME_ZP 来自 frame_head 输出 intq 声明（bit 判决零点基准）
// - 当模型重新量化后，必须同步更新本段参数
// ====================================================================
#define AI_INPUT_SCALE        (0.04223548248410225f) // input scale
#define AI_INPUT_ZP           (3)                    // input zero-point
#define AI_NORM_EPS           (1.0e-5f)              // 归一化防除零保护项

#define AI_FRAME_ZP           (-14)                  // frame 输出零点（量化域判决阈值基准）

// 结构映射参数：由 frame_bits / samples_per_bit / stride 推导
#define AI_STRIDE             (3)                    // 模型前端总步长
#define AI_LATENT_SAMPLES     (256)                  // 32*24/3
#define AI_LATENT_SPB         (8)                    // 24/3

// 后处理鲁棒性参数：边界候选、同步头容错、起点细修
#define AI_BOUNDARY_TOP_K     (3)                    // boundary Top-K 候选数
#define AI_BOUNDARY_AMBIGUOUS_THRESHOLD  (4)         // Top1-Top2 小于该值视为“边界模糊”
#define INFER_TIMEOUT_MS      (300)                  // 推理超时保护
#define SYNC_MAX_ERR          (0)                    // 同步头最大允许错误位数
#define SYNC_SHIFT_RANGE      (6)                    // 起点细修范围：[-6,+6]

// 调试开关（常规信息默认打印；详细诊断由 DEBUG_VERBOSE_LOG 控制）
#define AI_REPLAY_MODE        (1)                    // 1: 使用 test_sample_frame.h 注入离线样本


static float32_t adc_f32_buf[FRAME_SAMPLES];

#if AI_REPLAY_MODE
static uint8_t replay_pending_log = 0;   // 仅对“注入的那一帧”打印 REPLAY 日志
#endif

// ====================================================================
// AI 帧输出 bit 判决函数（量化域加权判决）
// 判决策略：
// - 每个 bit 对应 8 个 latent 点，采用加权窗口 [1,2,2,2,2,2,2,1]
// - 阈值使用 14*AI_FRAME_ZP，在量化域直接比较，避免反量化开销
// 工业意义：
// - 边缘点权重低、中心点权重高，可降低相位偏移与窄带噪声影响
// ====================================================================
static inline uint8_t DecodeFrameBitWeighted(const int8_t* frame, int base)
{
    int32_t acc = 0;
    acc += 1 * frame[base + 0];
    acc += 2 * frame[base + 1];
    acc += 2 * frame[base + 2];
    acc += 2 * frame[base + 3];
    acc += 2 * frame[base + 4];
    acc += 2 * frame[base + 5];
    acc += 2 * frame[base + 6];
    acc += 1 * frame[base + 7];

    return (acc > (14 * (int32_t)AI_FRAME_ZP)) ? 1U : 0U;
}

// ==========================================
// 预留接口区
// ==========================================
void Restore_Work_Mode(void) {
    // 井下系统上电时，从 Flash 读取之前的工作模式
    // is_continuous_mode = Flash_Read_Mode(); 
}

void Save_Work_Mode(void) {
    // 当收到新指令改变模式时，保存到 Flash
    // Flash_Write_Mode(is_continuous_mode);
}

void Perform_Hardware_Sweep(void) {
    // 对应老代码的 0xAA 扫频指令，用于评估物理信道
    // AD9833_SweepFrequency(10, 10000, 10, 50); 
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
  __disable_irq(); // 屏蔽中断进行时序敏感的初始化
  
  // 1. 初始化发波器
  AD9833_Init();
  AD9833_SetFreq(100, 0); 
  AD9833_SetFreq(200, 1); 
  AD9833_SelectFreq(0);   

  // 2) AI Runtime 初始化
  //    a) 创建网络实例
  //    b) 绑定权重区与激活区
  //    c) 初始化网络，失败时进入 Error_Handler
  ai_error ai_err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (ai_err.type != AI_ERROR_NONE) {
      printf("[AI] create failed: type=%d code=%d\r\n", ai_err.type, ai_err.code);
      Error_Handler();
  }

  const ai_network_params ai_params = {
      AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get()), 
      AI_NETWORK_DATA_ACTIVATIONS(activations)                
  };
  if (!ai_network_init(network, &ai_params)) {
      ai_err = ai_network_get_error(network);
      printf("[AI] init failed: type=%d code=%d\r\n", ai_err.type, ai_err.code);
      Error_Handler();
  }
  printf("[AI] model ready. INT8 network initialized.\r\n");

  // 3. 从 Flash 恢复上次断电前的模式
  Restore_Work_Mode();

  // 4. 传感器初始化与首次转换启动（可选）
#if USE_DS18B20
  DS18B20_Init();
  DS18B20_StartConvert(); 
#endif

  // 5. 启动 ADC 倾听
  HAL_TIM_Base_Start(&htim2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);

  // 中断优先级：ADC/DMA 与触发定时器高于 TIM3 发送
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
  
  __enable_irq(); // 系统就绪，放开中断

  printf("Underground Node Initialized!\r\n");
  printf("[Current State] state=%d\r\n", current_state);
 #if AI_REPLAY_MODE
  printf("[REPLAY] One-frame test loaded. SNR=%.1f dB, payload=0x%04X\r\n",
         (double)TEST_FRAME_SNR_DB,
         (unsigned int)TEST_FRAME_PAYLOAD16);
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    switch (current_state) {
        
        case STATE_LISTENING:
            // 硬件隔离底线
            APoff(); TXrelayOff(); RXrelayOn();

            // 监听态转推理态：当 DMA 完成一帧采样后进入 AI 解调流程
            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.inferStartTick = HAL_GetTick();
                current_state = STATE_INFERENCING;
               // printf("[Current State] state=%d (INFERENCING) \r\n", current_state);
            }
            // 连续回传逻辑暂不启用
            else if (is_continuous_mode) {
                // 预留：后续可在此处加入定时触发逻辑
            }
            
            
#if AI_REPLAY_MODE
            // 测试模式：仅注入一次离线波形（不循环）
            static uint8_t replay_once_done = 0;
            if (!replay_once_done) {
                replay_once_done = 1;
                memcpy(adc_dma_buffer, g_test_adc_frame, sizeof(g_test_adc_frame));
                demodCtrl.adcReadyFlag = 1;
                demodCtrl.inferStartTick = HAL_GetTick();
#if AI_REPLAY_MODE
                replay_pending_log = 1;
#endif
                current_state = STATE_INFERENCING;
                printf("[Current State] state=%d\r\n", current_state);
            }
#endif
            
            
            break;

        case STATE_INFERENCING:
        {
            uint8_t need_to_reply = 0; // 是否需要回传数据的标志

            if ((HAL_GetTick() - demodCtrl.inferStartTick) > INFER_TIMEOUT_MS) {
                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
                break;
            }

            // ==========================================
            // 分支 A：ADC 触发路径（主路径）
            // 流程：预处理量化 -> AI 推理 -> 边界/同步头后处理 -> 协议解析
            // ==========================================
            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.adcReadyFlag = 0;
                
                // 1) 预处理与量化（与 Ground/Core/Src/main.c 对齐）
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    adc_f32_buf[i] = (float32_t)adc_dma_buffer[i];
                }

                float32_t mean_f = 0.0f;
                float32_t std_f = 1.0f;

                arm_mean_f32(adc_f32_buf, FRAME_SAMPLES, &mean_f);
                arm_std_f32(adc_f32_buf, FRAME_SAMPLES, &std_f);
                if (std_f < AI_NORM_EPS) std_f = AI_NORM_EPS;

                const float32_t inv_std = 1.0f / std_f;
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    float32_t norm = (adc_f32_buf[i] - mean_f) * inv_std;
                    float32_t fq = (float32_t)(norm / AI_INPUT_SCALE);
                    int32_t q = (int32_t)(fq + (fq >= 0.0f ? 0.5f : -0.5f)) + (int32_t)AI_INPUT_ZP;
                    if (q > 127) q = 127;
                    if (q < -128) q = -128;
                    ai_in_buffer[i] = (int8_t)q;
                }

                // 2) AI 推理（双头输出）
                //    output[0]: boundary 头（用于起点定位）
                //    output[1]: frame 头（用于逐 bit 判决）
                ai_buffer *ai_input = ai_network_inputs_get(network, NULL);
                ai_input[0].data = AI_HANDLE_PTR(ai_in_buffer);

                ai_buffer *ai_output = ai_network_outputs_get(network, NULL);
                ai_output[0].data = AI_HANDLE_PTR(ai_out_boundary);
                ai_output[1].data = AI_HANDLE_PTR(ai_out_frame);

                ai_i32 n_batch = ai_network_run(network, ai_input, ai_output);
                if (n_batch != 1) {
                    ai_error run_err = ai_network_get_error(network);
                    printf("[AI] run failed: batch=%ld type=%d code=%d\r\n",
                           (long)n_batch, run_err.type, run_err.code);
               //     demodCtrl.syncMatched = 0;
                    HAL_ADC_Stop_DMA(&hadc1);
                    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                    current_state = STATE_LISTENING;
                    break;
                }

                // 3) boundary Top-3 候选（仅后处理，不增加推理次数）
                //    目的：当 Top1 与 Top2 分数接近时，避免单候选误定位
                int best_idx = 0;
                int8_t best_val = ai_out_boundary[0];
                int second_idx = 0;
                int8_t second_val = (int8_t)-128;
                int third_idx = 0;
                int8_t third_val = (int8_t)-128;

                for (int i = 1; i < AI_NETWORK_OUT_1_SIZE; i++) {
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

                int candidate_idxs[AI_BOUNDARY_TOP_K] = {best_idx, second_idx, third_idx};
                int candidate_count = 1;
                if ((best_val - second_val) <= AI_BOUNDARY_AMBIGUOUS_THRESHOLD) {
                    candidate_count = AI_BOUNDARY_TOP_K;
                }
                const uint8_t syncRef8 = 0xB6U; // 同步头 10110110
                uint8_t head_ok = 0;
                uint8_t best_head_err = 8;
                int best_start = 0;
                int best_addr_score = -1;
                uint8_t has_candidate = 0;

                // 4) Top-K 候选 + 局部移位细修 + 联合评分（sync+addr）
                for (int c = 0; c < candidate_count; c++) {
                    int center = candidate_idxs[c];

                    for (int delta = -SYNC_SHIFT_RANGE; delta <= SYNC_SHIFT_RANGE; delta++) {
                        int start = center + delta;
                        if (start < 0) start = 0;
                        if (start > (AI_NETWORK_OUT_2_SIZE - AI_LATENT_SAMPLES)) {
                            start = (AI_NETWORK_OUT_2_SIZE - AI_LATENT_SAMPLES);
                        }

                        // 无数组实现：边解前16bit，边统计head_err并组装地址
                        uint8_t head_err = 0;
                        uint8_t cand_dest = 0;
                        uint8_t cand_src = 0;

                        for (int bit = 0; bit < 16; bit++) {
                            int base = start + bit * AI_LATENT_SPB;
                            uint8_t hb = (uint8_t)(DecodeFrameBitWeighted(ai_out_frame, base) & 0x01U);

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
                        if (cand_dest == LOCAL_ADDRESS) addr_score += 2;
                        if (cand_src == ADDR_GROUND)   addr_score += 1;

                        // 联合最优策略：先最小 head_err，再最大 addr_score
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

                if (has_candidate && best_head_err <= SYNC_MAX_ERR) {
                    head_ok = 1;
                }

    //            demodCtrl.syncMatched = head_ok ? 1U : 0U;

                // 仅在同步头通过时，才对最佳起点解完整 32 bit（打包为 uint32_t）
                if (head_ok) {
                    uint32_t rf = 0U;
                    for (int bit = 0; bit < FRAME_BITS; bit++) {
                        int base = best_start + bit * AI_LATENT_SPB;
                        rf = (rf << 1) | (uint32_t)(DecodeFrameBitWeighted(ai_out_frame, base) & 0x01U);
                    }
                    demodCtrl.rxFrame = rf;
                }

       /*         if (!head_ok) {
                    printf("[RX-ERR] frame dropped: sync header mismatch (head_err=%u, th=%u)\r\n",
                           best_head_err, (uint8_t)SYNC_MAX_ERR);
                }*/

                if (head_ok) {
                    demodCtrl.destAddr = (uint8_t)((demodCtrl.rxFrame >> 20) & 0x0FU);
                    demodCtrl.srcAddr  = (uint8_t)((demodCtrl.rxFrame >> 16) & 0x0FU);
                    demodCtrl.payloadData = (uint32_t)(demodCtrl.rxFrame & 0xFFFFU);

                    uint8_t cmd_code = (uint8_t)(demodCtrl.payloadData & 0xFFU);

#if AI_REPLAY_MODE
                    if (replay_pending_log) {
                        printf("[Command]: dst=0x%X src=0x%X cmd=0x%02X\r\n",
                               demodCtrl.destAddr,
                               demodCtrl.srcAddr,
                               cmd_code);
                        replay_pending_log = 0;
                    }
#endif

                    if (demodCtrl.destAddr == LOCAL_ADDRESS) {

                        switch(cmd_code) {
                            case 0x19: 
                            case 0x4B: 
                            case 0x7D: 
                            case 0x9C: 
                                is_continuous_mode = 0;
                                Save_Work_Mode(); 
                                need_to_reply = 1; 
                                break;
                                
                            case 0x55:
                                // 连续回传功能暂不启用，保留命令入口
                                is_continuous_mode = 0;
                                Save_Work_Mode(); 
                                need_to_reply = 1; 
                                break;
                                
                            case 0xAA:
                                Perform_Hardware_Sweep();
                                need_to_reply = 0; 
                                break;
                                
                            default:
                                need_to_reply = 0; 
                                break;
                        }
                    }
                }
            }
            // ==========================================
            // 分支 B：连续回传预留路径（当前关闭）
            // 说明：保留接口，不参与当前版本主流程。
            // ==========================================
            else {
                need_to_reply = 0;
            }

            // ==========================================
            // 回传发送交接区
            // 触发条件：命令解析通过且命令类型要求回传。
            // ==========================================
            if (need_to_reply) {
                // 防止在尚未完成上一帧发送时重复进入发送流程
                if (modCtrl.isTransmitting) {
                    current_state = STATE_TRANSMITTING;
                } else {
                    uint8_t t_u8, p_u8;

#if USE_DS18B20
                    // 1) 读取温度（取整数部分）并启动下一次转换
                    real_temperature = DS18B20_ReadTemp();
                    DS18B20_StartConvert();

                    // DS18B20_ReadTemp() 已返回整数温度（uint8），无小数参与组包
                    t_u8 = real_temperature;
                    p_u8 = 102; // 预留压力通道：先给固定值，后续可替换为真实压力传感器
#else
                    // 无传感器实验模式：使用固定温压数据
                    t_u8 = 58;
                    p_u8 = 86;
#endif

                    // 2) V7 载荷：payload16 = [temp8][pres8]
                    uint32_t tp_packet = ((uint32_t)t_u8 << 8) | (uint32_t)p_u8;
                    
                    // 3. 构建信封
                    BuildTxFrame(ADDR_GROUND, LOCAL_ADDRESS, tp_packet);

                    // 常规调试：组包完成后打印地址与温压数据
                    printf("[TX] dst=0x%X src=0x%X temp=%u pres=%u payload=0x%04lX frame=0x%08lX\r\n",
                           ADDR_GROUND,
                           LOCAL_ADDRESS,
                           t_u8,
                           p_u8,
                           (unsigned long)tp_packet,
                           (unsigned long)modCtrl.txFrame);
                    
                    // 4) 射频发射链路切换：先停采样，再切换继电器与功放使能
                    HAL_ADC_Stop_DMA(&hadc1); 
                    demodCtrl.adcReadyFlag = 0;
                    RXrelayOff(); TXrelayOn(); APon(); 
                    HAL_Delay(15); //  关键缓冲：等待继电器彻底吸合，防烧功放
                
                    // 5) 启动发送状态机（TIM3 周期中断逐 bit 发射）
                    modCtrl.txBitIndex = 0;
                    modCtrl.isTransmitting = 1;
                    HAL_TIM_Base_Start_IT(&htim3);
                    current_state = STATE_TRANSMITTING;
                    printf("[Current State] state=%d\r\n",
                           current_state);
                }
            } 
            else {
                // 如果是误触发(无回复必要)，清空状态继续监听
                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
            }
            break;
        }

        case STATE_TRANSMITTING:
            if (modCtrl.isTransmitting == 0) { 
                // 发送结束收尾：关闭功放与发射继电器，恢复接收链路
                APoff(); TXrelayOff(); HAL_Delay(5); RXrelayOn();   
                
                // 更新时间锚点：记录本次发送完成时刻（用于后续节拍控制）
                last_tx_timestamp = HAL_GetTick();
                
                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
                printf("[TX] Data sent successfully.\r\n");
                printf("[Current State] state=%d\r\n",
                       current_state
                       );

            }
            break;
    }
  /* USER CODE END 3 */
 }
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

// ====================================================================
// 1. ADC 接收完成中断
// ====================================================================
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1 && current_state == STATE_LISTENING) {
        demodCtrl.adcReadyFlag = 1; 
    }
}

// ====================================================================
// 2. TIM3 定时发送中断
// ====================================================================
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
                modCtrl.txBitIndex = -1;       
                modCtrl.isTransmitting = 0;    
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
