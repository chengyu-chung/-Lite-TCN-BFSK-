#ifndef __DS18B20_H
#define __DS18B20_H

#include "main.h"

// ==========================================
// 硬件引脚配置 (请务必在 CubeMX 中将此引脚配为 Output Open Drain 开漏输出)
// ==========================================
#define DS18B20_PORT GPIOA
#define DS18B20_PIN  GPIO_PIN_1

// ==========================================
// 寄存器级快速 I/O 控制宏 (提高 1-Wire 翻转速度)
// ==========================================
#define DS18B20_OUT_H()  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET)
#define DS18B20_OUT_L()  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET)
#define DS18B20_IN()     HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)

// ==========================================
// 函数声明
// ==========================================
// 底层微秒延时
void DWT_Delay_Init(void);
void delay_us(uint32_t us);

// 应用层控制接口
uint8_t DS18B20_Init(void);
void    DS18B20_StartConvert(void);
uint8_t DS18B20_WaitForConversion(uint32_t timeout_ms);
uint8_t DS18B20_ReadTemp(void);

#endif /* __DS18B20_H */
