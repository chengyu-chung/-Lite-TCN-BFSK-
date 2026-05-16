/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  * This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

// ====================================================================
// 1) 物理层参数（与 AI 模型输入/后处理强绑定）
//    说明：以下宏变更时，必须同步更新训练脚本与三端固件。
// ====================================================================
#define FRAME_BITS       32   // 帧结构：sync(8)+dest(4)+src(4)+payload(16)
#define TAIL_BITS        4    // 发射尾部补零位（便于收端恢复静默）
#define FRAME_SAMPLES    960  // 单帧输入采样点数（与 ONNX 输入尺寸一致）

// ====================================================================
// 2) AI 解调控制结构体
//    作用：承载“采样完成 -> AI推理 -> 协议解析”全链路状态。
// ====================================================================
typedef struct {
    uint8_t   adcReadyFlag;        // ADC 一帧采样完成标志（1=ready）
    uint32_t  inferStartTick;      // 推理起始时间戳（用于超时保护）

    // 协议解析结果（仅在同步头校验通过后有效）
//    uint8_t   syncMatched;         // 同步头匹配标志
    uint8_t   destAddr;            // 目标地址（4bit）
    uint8_t   srcAddr;             // 源地址（4bit）
    uint32_t  payloadData;         // 载荷缓存（V7 有效位为低 16bit）

    // AI 后处理输出（32bit 帧，MSB first）
    uint32_t  rxFrame;             // 解出的 32bit 数据帧
} AI_Demod_Ctrl_t;

// ====================================================================
// 3) 发送调制控制结构体
//    作用：承载下行发送状态机与待发送比特缓存。
// ====================================================================
typedef struct {
    uint8_t   isTransmitting;      // 发送状态（1=发送中，0=空闲）
    int16_t   txBitIndex;          // 当前发送索引（0 ~ FRAME_BITS+TAIL_BITS-1）

    uint16_t  freq0;               // bit=0 频率（Hz）
    uint16_t  freq1;               // bit=1 频率（Hz）

    uint32_t  txFrame;             // 待发送32bit帧（MSB first）
} Modulate_Ctrl_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Send_Command_To_Underground(uint8_t cmd);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD9833FSYNC_Pin GPIO_PIN_4
#define AD9833FSYNC_GPIO_Port GPIOA
#define RELAY_TX_CTRL_Pin GPIO_PIN_5
#define RELAY_TX_CTRL_GPIO_Port GPIOB
#define RELAY_RX_CTRL_Pin GPIO_PIN_6
#define RELAY_RX_CTRL_GPIO_Port GPIOB
#define AP_MUTE_CTRL_Pin GPIO_PIN_7
#define AP_MUTE_CTRL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

// ==========================================
// 4. 井下网络节点地址定义 (完全保留经典网络拓扑)
// ==========================================
#define ADDR_GROUND      0x0  // 井上地址：0000

#define ADDR_RELAY1      0x1  // 中继1地址：0001
#define ADDR_RELAY2      0x2  // 中继2地址：0010
#define ADDR_RELAY3      0x3  // 中继3地址：0011
#define ADDR_RELAY4      0x4  // 中继4地址：0100
#define ADDR_RELAY5      0x5  // 中继5地址：0101
#define ADDR_RELAY6      0x6  // 中继6地址：0110
#define ADDR_RELAY7      0x7  // 中继7地址：0111
#define ADDR_RELAY8      0x8  // 中继8地址：1000
#define ADDR_RELAY9      0x9  // 中继9地址：1001
#define ADDR_RELAY10     0xA  // 中继10地址：1010
#define ADDR_RELAY11     0xB  // 中继11地址：1011
#define ADDR_RELAY12     0xC  // 中继12地址：1100
#define ADDR_RELAY13     0xD  // 中继13地址：1101
#define ADDR_RELAY14     0xE  // 中继14地址：1110

#define ADDR_UNDERGROUND 0xF  // 井下地址：1111

// --- 本机身份配置 ---
#define LOCAL_ADDRESS    ADDR_GROUND // 当前设备的绝对物理地址

// ==========================================
// 5. 声明外部全局变量供 main.c 和 stm32l4xx_it.c 使用
// ==========================================
extern volatile AI_Demod_Ctrl_t demodCtrl;
extern volatile Modulate_Ctrl_t modCtrl;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
