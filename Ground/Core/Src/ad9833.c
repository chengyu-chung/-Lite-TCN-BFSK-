#include "ad9833.h"
#include "spi.h"

/**
  * @brief  向 AD9833 写入 16 位命令/数据
  * @param  data: 准备写入的 16 位原始数据
  * @note   该函数内部处理了 FSYNC (片选) 的电平翻转
  */
static void AD9833_Write(uint16_t data) {
    AD9833_FSYNC_0(); // 拉低片选，开始通信
    
    /* * 使用 HAL 库通过 SPI1 发送 16bit 数据。
     * 注意：需在 CubeMX 中将 SPI 的 Data Size 设置为 16-Bit。
     */
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&data, 1, 100);
    
    AD9833_FSYNC_1(); // 拉高片选，结束通信
}

/**
  * @brief  初始化 AD9833 芯片
  * @note   设置 B28 位为 1，允许连续写入两个 14 位频率字（共 28 位）
  */
void AD9833_Init(void) {
    AD9833_FSYNC_1(); // 初始状态下 FSYNC 保持高电平
    
    /* * 0x2100 含义：
     * [D13] B28 = 1 (允许 28 位连续写)
     * [D8]  RESET = 1 (进入复位状态，写频率时必须复位)
     */
    AD9833_Write(0x2100); 
}

/**
  * @brief  设置 AD9833 的频率寄存器
  * @param  freq: 目标输出频率 (Hz)
  * @param  regNum: 寄存器选择，0 代表 FREQ0, 1 代表 FREQ1
  * @note   本函数会自动将 Hz 转换为 AD9833 内部所需的频率字
  */
void AD9833_SetFreq(uint32_t freq, uint8_t regNum) {
    /* 核心公式：FreqReg = (f_out * 2^28) / f_MCLK */
    uint32_t freq_val = (uint32_t)((double)freq * AD9833_F_CONST / AD9833_MCLK);
    
    /* 将 28 位数据拆分为两个 14 位的数据块 */
    uint16_t LSB = (uint16_t)(freq_val & 0x3FFF);         // 提取低 14 位
    uint16_t MSB = (uint16_t)((freq_val >> 14) & 0x3FFF);  // 提取高 14 位
    
    /* 根据寄存器编号确定地址前缀 (FREQ0 = 0x4000, FREQ1 = 0x8000) */
    uint16_t reg_addr = (regNum == 0) ? AD9833_REG_FREQ0 : AD9833_REG_FREQ1;

    /* 按照 AD9833 时序要求进行分步写入 */
    AD9833_Write(0x2100);            // 保持复位状态并确保 B28=1
    AD9833_Write(reg_addr | LSB);    // 写入频率字低 14 位
    AD9833_Write(reg_addr | MSB);    // 写入频率字高 14 位
    AD9833_Write(0x2000);            // 退出复位模式，芯片开始输出正弦波
}

/**
  * @brief  快速切换输出频率 (BFSK 调制的核心函数)
  * @param  regNum: 0 选中 FREQ0 (通常设为 f0), 1 选中 FREQ1 (通常设为 f1)
  * @note   通过修改控制寄存器的 FSELECT 位实现无缝切换
  */
void AD9833_SelectFreq(uint8_t regNum) {
    if (regNum == 0) {
        AD9833_Write(0x2000); 
    } else {
        AD9833_Write(0x2800); 
    }
}
