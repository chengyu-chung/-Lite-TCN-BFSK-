#ifndef __AD9833_H__
#define __AD9833_H__

#include "main.h"

// --- 硬件引脚定义 (根据你的引脚图定义) ---
#define AD9833_FSYNC_0()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define AD9833_FSYNC_1()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

// --- AD9833 寄存器指令宏 ---
#define AD9833_REG_CMD    0x2000
#define AD9833_REG_FREQ0  0x4000
#define AD9833_REG_FREQ1  0x8000
#define AD9833_REG_PHASE0 0xC000

// --- 频率计算常数 (假设你的 MCLK 是 25MHz) ---
#define AD9833_MCLK       25000000.0
#define AD9833_F_CONST    268435456.0 // 2^28

// 函数声明
void AD9833_Init(void);
void AD9833_SetFreq(uint32_t freq, uint8_t regNum);
void AD9833_SelectFreq(uint8_t regNum);

#endif

