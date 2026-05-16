/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  * the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

// 命令结构体定义 (实际内存占用大于5字节，发送时在底层的 SendCommand 中会被压缩打包为5字节)
typedef struct {
    uint8_t mask;              // 8位掩码
    uint8_t dest_addr;         // 4位目的地址 (高4位留空)
    uint8_t src_addr;          // 4位源地址 (高4位留空)
    uint32_t cmd;              // 24位命令 (高8位留空)
} Command_TypeDef;

// 接收缓冲区定义
#define USART_RX_BUFFER_SIZE 256
#define USART_TX_BUFFER_SIZE 256

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

// 外部调用的 API 声明
uint8_t USART_SendCommand(Command_TypeDef *cmd);
uint8_t USART_ReceiveData(uint8_t *data, uint16_t *length);
void USART_StartReceive(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

