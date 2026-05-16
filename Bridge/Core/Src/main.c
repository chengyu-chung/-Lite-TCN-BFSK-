/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 井下通信中继站主程序 (Relay Node - AI核心强化版)
  * @note           : 中继节点实现透明转发，根据源地址判定转发方向。
  * 1. INT8 量化 TCN 解调，边界 Top-3 与严格同步头校验。
  * 2. 40 bit 解调后仅修改目的地址，载荷透明转发。
  * 3. 继电器切换加入 15ms 缓冲，降低硬件冲击。
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
#include "network.h"
#include "network_data.h"
#include "relay_control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// 核心三态状态机（中继专属）
typedef enum {
    STATE_LISTENING,   // 监听态：等待 ADC 采满一帧
    STATE_INFERENCING, // 推理态：AI 解调并执行路由判定
    STATE_TRANSMITTING // 发送态：转发已解调的数据帧
} SystemState_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 推理超时保护（防止异常卡在 INFERENCING）
#define INFER_TIMEOUT_MS 300
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// --- 系统控制与状态机 ---
SystemState_t current_state = STATE_LISTENING; // 上电默认状态设为倾听

// 核心控制器实例化
volatile AI_Demod_Ctrl_t demodCtrl = {0};
volatile Modulate_Ctrl_t modCtrl = {0};

uint16_t adc_dma_buffer[FRAME_SAMPLES];

// AI 模型专属内存区
AI_ALIGNED(4) static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
static ai_handle network = AI_HANDLE_NULL;

// INT8 量化输入/输出缓冲区
int8_t ai_in_buffer[FRAME_SAMPLES];
int8_t ai_out_boundary[AI_NETWORK_OUT_1_SIZE];
int8_t ai_out_frame[AI_NETWORK_OUT_2_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ====================================================================
// 量化与后处理参数（与 Ground/Underground 对齐）
// ====================================================================
#define AI_INPUT_SCALE        (0.04032759368419647f)
#define AI_INPUT_ZP           (-5)
#define AI_NORM_EPS           (1.0e-5f)
#define AI_FRAME_ZP           (13)
#define AI_STRIDE             (3)
#define AI_LATENT_SAMPLES     (320)
#define AI_LATENT_SPB         (8)
#define AI_BOUNDARY_TOP_K     (3)
#define AI_BOUNDARY_AMBIGUOUS_THRESHOLD  (4)

static float32_t adc_f32_buf[FRAME_SAMPLES];

// ====================================================================
// 串口打印重定向（用于调试路由方向）
// ====================================================================
int fputc(int ch, FILE *f) {
    extern UART_HandleTypeDef huart1; 
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// ====================================================================
// 下行帧组包（中继用于改写目的地址后转发）
// ====================================================================
void BuildTxFrame(uint8_t destAddr, uint8_t srcAddr, uint32_t payloadData) {
    uint8_t syncHead[8] = {1, 1, 1, 0, 0, 1, 0, 1};
    for(int i = 0; i < 8; i++) modCtrl.txBuffer[i] = syncHead[i];
    
    for(int i = 0; i < 4; i++) modCtrl.txBuffer[8+i] = (destAddr >> (3-i)) & 0x01;
    for(int i = 0; i < 4; i++) modCtrl.txBuffer[12+i] = (srcAddr >> (3-i)) & 0x01;
    for(int i = 0; i < 24; i++) modCtrl.txBuffer[16+i] = (payloadData >> (23-i)) & 0x01;
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
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  // ==========================================
  // 初始化期间关闭全局中断，防止时序错乱
  // ==========================================
  __disable_irq();
  
  // 1. 初始化 AD9833 硬件波形发生器
  AD9833_Init();
  AD9833_SetFreq(100, 0); 
  AD9833_SetFreq(200, 1); 
  AD9833_SelectFreq(0);   

  // 2. 唤醒并初始化 MicroTCN 深度学习网络模型
  ai_error err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
      while(1); 
  }
  const ai_network_params ai_params = {
      AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get()), 
      AI_NETWORK_DATA_ACTIVATIONS(activations)                
  };
  if (!ai_network_init(network, &ai_params)) {
      while(1); 
  }

  // 3. 开启定时器 TIM2 (ADC 的硬件触发源，1200Hz)
  HAL_TIM_Base_Start(&htim2);

  // 4. 启动 ADC DMA 持续采集
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);

  // 中断优先级：ADC/DMA 高于 TIM3 发送
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
  
  __enable_irq();

  // 打印初始化成功信息及本中继地址
  printf("Relay Station Init Success! Addr: 0x%02X\r\n", LOCAL_ADDRESS);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    switch (current_state) {
        
        case STATE_LISTENING:
            APoff(); TXrelayOff(); RXrelayOn();

            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.inferStartTick = HAL_GetTick();
                current_state = STATE_INFERENCING;
            }
            break;

        case STATE_INFERENCING:
        {
            if ((HAL_GetTick() - demodCtrl.inferStartTick) > INFER_TIMEOUT_MS) {
                HAL_ADC_Stop_DMA(&hadc1);
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING;
                break;
            }

            if (demodCtrl.adcReadyFlag == 1) {
                demodCtrl.adcReadyFlag = 0;

                // 1) 预处理与量化（与 Ground/Underground 对齐）
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    adc_f32_buf[i] = (float32_t)adc_dma_buffer[i];
                }

                float32_t mean_f = 0.0f;
                float32_t std_f = 1.0f;

                arm_mean_f32(adc_f32_buf, FRAME_SAMPLES, &mean_f);
                arm_std_f32(adc_f32_buf, FRAME_SAMPLES, &std_f);
                if (std_f < AI_NORM_EPS) std_f = AI_NORM_EPS;

                const float32_t inv_std = 1.0f / (std_f + AI_NORM_EPS);
                for (int i = 0; i < FRAME_SAMPLES; i++) {
                    float32_t norm = (adc_f32_buf[i] - mean_f) * inv_std;
                    float32_t fq = (float32_t)(norm / AI_INPUT_SCALE);
                    int32_t q = (int32_t)(fq + (fq >= 0.0f ? 0.5f : -0.5f)) + (int32_t)AI_INPUT_ZP;
                    if (q > 127) q = 127;
                    if (q < -128) q = -128;
                    ai_in_buffer[i] = (int8_t)q;
                }

                // 2) AI 推理
                ai_buffer *ai_input = ai_network_inputs_get(network, NULL);
                ai_input[0].data = AI_HANDLE_PTR(ai_in_buffer);
                
                ai_buffer *ai_output = ai_network_outputs_get(network, NULL);
                ai_output[0].data = AI_HANDLE_PTR(ai_out_boundary);
                ai_output[1].data = AI_HANDLE_PTR(ai_out_frame);

                ai_network_run(network, ai_input, ai_output);

                // 3) boundary Top-3 候选（仅后处理，不增加推理次数）
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
                const uint8_t syncRef[8] = {1,1,1,0,0,1,0,1};
                uint8_t head_ok = 0;

                // 4) Top-3 解调 + 同步头严格匹配（0 误差）
                for (int c = 0; c < candidate_count; c++) {
                    int start = candidate_idxs[c];
                    if (start < 0) start = 0;
                    if (start > (AI_NETWORK_OUT_2_SIZE - AI_LATENT_SAMPLES)) {
                        start = (AI_NETWORK_OUT_2_SIZE - AI_LATENT_SAMPLES);
                    }
                    
                    uint8_t local_bits[FRAME_BITS];
                    for (int bit = 0; bit < FRAME_BITS; bit++) {
                        int base = start + bit * AI_LATENT_SPB;
                        int32_t sum5 = 0;
                        sum5 += ai_out_frame[base + 2];
                        sum5 += ai_out_frame[base + 3];
                        sum5 += ai_out_frame[base + 4];
                        sum5 += ai_out_frame[base + 5];
                        sum5 += ai_out_frame[base + 6];
                        local_bits[bit] = (sum5 > (5 * AI_FRAME_ZP)) ? 1 : 0;
                    }

                    uint8_t ok = 1;
                    for (int i = 0; i < 8; i++) {
                        if (local_bits[i] != syncRef[i]) {
                            ok = 0;
                            break;
                        }
                    }

                    if (ok) {
                        for (int i = 0; i < FRAME_BITS; i++) {
                            demodCtrl.rawBits[i] = local_bits[i];
                        }
                        head_ok = 1;
                        break;
                    }
                }

                if (head_ok) {
                    demodCtrl.destAddr = (demodCtrl.rawBits[8] << 3)  | (demodCtrl.rawBits[9] << 2)  | 
                                         (demodCtrl.rawBits[10] << 1) | demodCtrl.rawBits[11];
                    
                    demodCtrl.srcAddr  = (demodCtrl.rawBits[12] << 3) | (demodCtrl.rawBits[13] << 2) | 
                                         (demodCtrl.rawBits[14] << 1) | demodCtrl.rawBits[15];

                    demodCtrl.payloadData = 0;
                    for(int i = 16; i < 40; i++) {
                        demodCtrl.payloadData = (demodCtrl.payloadData << 1) | demodCtrl.rawBits[i];
                    }

                    // 路由判定与转发
                    if (demodCtrl.destAddr != LOCAL_ADDRESS) {
                        printf("Dropped packet for 0x%02X\r\n", demodCtrl.destAddr);
                        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                        current_state = STATE_LISTENING;
                    } 
                    else {
                        uint8_t nextDestAddr;

                        // 单中继场景：下行直接到井下，上行直接到井上
                        // 多中继场景：可将目的地址改为逐级转发（如 LOCAL_ADDRESS+1 或 LOCAL_ADDRESS-1）
                        // 若要启用逐级转发，请替换下面两行赋值逻辑即可
                        if (demodCtrl.srcAddr < LOCAL_ADDRESS) {
                            nextDestAddr = ADDR_UNDERGROUND; 
                            printf("Routing Down -> Dest: 0x%02X\r\n", nextDestAddr);
                        } 
                        else if (demodCtrl.srcAddr > LOCAL_ADDRESS) {
                            nextDestAddr = ADDR_GROUND;
                            printf("Routing Up -> Dest: 0x%02X\r\n", nextDestAddr);
                        } 
                        else {
                            nextDestAddr = demodCtrl.destAddr; 
                        }

                        if (modCtrl.isTransmitting) {// 当前正在发送，直接丢弃新帧并继续当前发送
                            current_state = STATE_TRANSMITTING;
                        } else {// 当前没有正在发送，开始处理新帧
                            BuildTxFrame(nextDestAddr, LOCAL_ADDRESS, demodCtrl.payloadData);
                            
                            HAL_ADC_Stop_DMA(&hadc1);
                            demodCtrl.adcReadyFlag = 0;
                            
                            RXrelayOff();
                            TXrelayOn();
                            APon();
                            HAL_Delay(15);//延时15ms，等待TX relay打开和AP开启完成，降低硬件冲击
                            
                            modCtrl.txBitIndex = 0;     
                            modCtrl.isTransmitting = 1; 
                            HAL_TIM_Base_Start_IT(&htim3); 
                            current_state = STATE_TRANSMITTING;
                        }
                    }
                }
                else {// 同步头匹配失败，继续监听下一帧
                    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                    current_state = STATE_LISTENING;
                }
            }
            break;
        }

        case STATE_TRANSMITTING:
            if (modCtrl.isTransmitting == 0) { 
                APoff();
                TXrelayOff();
                HAL_Delay(5);
                RXrelayOn();
                
                HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, FRAME_SAMPLES);
                current_state = STATE_LISTENING; 
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
// 1. ADC 接收完成中断 (由硬件 DMA 自动触发)
// ====================================================================
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1 && current_state == STATE_LISTENING) {
        demodCtrl.adcReadyFlag = 1; 
    }
}

// ====================================================================
// 2. TIM3 定时发送中断 (物理层 BFSK 调制输出)
// ====================================================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        if (modCtrl.isTransmitting && modCtrl.txBitIndex >= 0 && modCtrl.txBitIndex < (FRAME_BITS + TAIL_BITS)) {
            
            if (modCtrl.txBitIndex < FRAME_BITS) {
                // A 段：发送真正的 40 位 AI 数据帧
                if (modCtrl.txBuffer[modCtrl.txBitIndex] == 1) {
                    AD9833_SelectFreq(1); 
                } else {
                    AD9833_SelectFreq(0); 
                }
            } 
            else {
                // B 段：隐形尾随保护 (Tail Bits)，发 0 降频
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
