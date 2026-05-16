/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  * of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

// 接收缓冲区
static uint8_t usart_rx_buffer[USART_RX_BUFFER_SIZE];
// 加上 volatile，因为该变量在主循环和中断中都会被访问
static volatile uint16_t usart_rx_index = 0; 
static uint8_t usart_rx_temp;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

// 发送命令函数：将40位命令打包成5个字节并发送
uint8_t USART_SendCommand(Command_TypeDef *cmd)
{
    uint8_t tx_data[5];
    
    if (cmd == NULL) {
        return 0;
    }
    
    // 打包数据：
    // 字节0: mask (8位)
    tx_data[0] = cmd->mask;
    
    // 字节1: dest_addr(4位) + src_addr(4位)
    tx_data[1] = ((cmd->dest_addr & 0x0F) << 4) | (cmd->src_addr & 0x0F);
    
    // 字节2-4: cmd (24位，分成3个字节)
    tx_data[2] = (cmd->cmd >> 16) & 0xFF;
    tx_data[3] = (cmd->cmd >> 8) & 0xFF;
    tx_data[4] = cmd->cmd & 0xFF;
    
    // 通过UART发送5个字节
    if (HAL_UART_Transmit(&huart1, tx_data, 5, 100) == HAL_OK) {
        return 1;
    }
    return 0;
}

// 接收函数
uint8_t USART_ReceiveData(uint8_t *data, uint16_t *length)
{
    if (data == NULL || length == NULL) {
        return 0;
    }

    // --- 进入临界区，仅关闭 USART1 中断，不影响系统其他功能 ---
    HAL_NVIC_DisableIRQ(USART1_IRQn);

    if (usart_rx_index == 0) {
        HAL_NVIC_EnableIRQ(USART1_IRQn); // 恢复中断
        return 0;  // 没有数据
    }
    
    // 复制接收到的数据
    for (uint16_t i = 0; i < usart_rx_index; i++) {
        data[i] = usart_rx_buffer[i];
    }
    *length = usart_rx_index;
    
    // 清空缓冲区索引
    usart_rx_index = 0;
    
    // --- 退出临界区，恢复 USART1 中断 ---
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
    return 1;
}

// 启动接收（中断模式）
void USART_StartReceive(void)
{
    usart_rx_index = 0;
    HAL_UART_Receive_IT(&huart1, &usart_rx_temp, 1);
}

// UART接收中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        // 将接收到的字节存入缓冲区，如果满了则丢弃新数据，保护现有数据
        if (usart_rx_index < USART_RX_BUFFER_SIZE) {
            usart_rx_buffer[usart_rx_index++] = usart_rx_temp;
        }
        
        // 继续接收下一个字节
        HAL_UART_Receive_IT(&huart1, &usart_rx_temp, 1);
    }
}

// UART错误回调函数（防止串口假死）
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        // 清除所有常见错误标志 (溢出ORE, 噪声NE, 帧错误FE, 校验PE)
        __HAL_UART_CLEAR_OREFLAG(huart);
        __HAL_UART_CLEAR_NEFLAG(huart);
        __HAL_UART_CLEAR_FEFLAG(huart);
        __HAL_UART_CLEAR_PEFLAG(huart);
        
        // 错误发生后，HAL库会自动关闭接收，这里必须重新启动
        HAL_UART_Receive_IT(&huart1, &usart_rx_temp, 1);
    }
}

/* USER CODE END 1 */
