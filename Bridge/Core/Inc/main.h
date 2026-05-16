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

// ==========================================
// 1. 物理层参数定义 (AI 部署的硬指标)
// ==========================================
#define FRAME_BITS       40   // 一帧数据的总比特数
#define TAIL_BITS    4     // 物理层多发的 0
#define FRAME_SAMPLES    960  // 一帧数据的总采样点数 (1200Hz下采800ms)

// ==========================================
// 2. AI 解调控制结构体
// ==========================================
typedef struct {
    uint8_t   adcReadyFlag;      // ADC 960点采集完成标志 (1: 采满, 0: 未满)
    uint32_t  inferStartTick;    // 推理起始时间戳（超时保护）
    
    // 协议解析部分 
    uint8_t   syncMatched;       // 同步头是否匹配成功标志
    uint8_t   destAddr;          // 解析出的目标地址
    uint8_t   srcAddr;           // 解析出的源地址
    uint32_t  payloadData;       // 解析出的实际指令/数据载荷
    
    // AI 原始输出缓存
    uint8_t   rawBits[FRAME_BITS]; // AI 网络直接吐出的 40 个 0/1 比特
} AI_Demod_Ctrl_t;

// ==========================================
// 3. 发送调制控制结构体
// ==========================================
typedef struct {
    uint8_t   isTransmitting;    // 发送机工作状态标志 (1: 正在发送, 0: 空闲)
    int16_t   txBitIndex;        // 当前正在发送的比特索引 (0 ~ 39)
    
    uint16_t  freq0;             // 符号 0 对应的物理频率 (如 100Hz)
    uint16_t  freq1;             // 符号 1 对应的物理频率 (如 200Hz)
    
    uint8_t   txBuffer[FRAME_BITS]; // 待发送的比特缓冲区 (直接存储 0 和 1)
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
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
#define LOCAL_ADDRESS    ADDR_RELAY1 // 当前设备的绝对物理地址

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
