#include "ds18b20.h"

// ====================================================================
// ⏱️ 内核级微秒延时 (利用 Cortex-M4 DWT 计数器)
// ====================================================================
void DWT_Delay_Init(void) {
    // 允许 DWT 计数
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; 
    DWT->CYCCNT = 0;                                
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            
}

void delay_us(uint32_t us) {
    uint32_t startTick = DWT->CYCCNT;
    // SystemCoreClock 变量由 HAL 库维护，代表当前 CPU 频率 (如 80000000)
    uint32_t delayTicks = us * (SystemCoreClock / 1000000); 
    while (DWT->CYCCNT - startTick < delayTicks);
}

// ====================================================================
// 🔌 1-Wire 底层物理协议
// ====================================================================

/**
  * @brief  主机发送复位脉冲并检测从机存在脉冲
  * @retval 1: 检测到 DS18B20;  0: 未检测到
  */
static uint8_t DS18B20_Reset(void) {
    uint8_t presence = 0;
    
    DS18B20_OUT_L();   // 主机拉低总线
    delay_us(480);     // 保持 480us 发送复位脉冲
    DS18B20_OUT_H();   // 释放总线，外部上拉电阻将其拉高
    delay_us(60);      // 延时 60us 等待 DS18B20 响应
    
    // 检查 DS18B20 是否拉低总线 (回应存在脉冲)
    if (DS18B20_IN() == GPIO_PIN_RESET) {
        presence = 1;  
    } else {
        presence = 0;  
    }
    
    delay_us(420);     // 等待时隙结束 (最少 480us，已过 60us，补 420us)
    return presence;
}

/**
  * @brief  向 DS18B20 写入一个字节 (低位先行 LSB First)
  */
static void DS18B20_WriteByte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        DS18B20_OUT_L(); // 产生写时隙起始信号
        delay_us(2);     // 保持 2us
        
        if (data & 0x01) {
            DS18B20_OUT_H(); // 写入逻辑 1：提前释放总线
        } else {
            DS18B20_OUT_L(); // 写入逻辑 0：继续拉低总线
        }
        delay_us(60);        // 保持时隙至少 60us
        DS18B20_OUT_H();     // 释放总线，准备下一位
        delay_us(2);         // 两次写时隙间的恢复时间
        
        data >>= 1;          // 移位准备下一比特
    }
}

/**
  * @brief  从 DS18B20 读取一个字节 (低位先行 LSB First)
  */
static uint8_t DS18B20_ReadByte(void) {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        data >>= 1;
        
        DS18B20_OUT_L(); // 产生读时隙起始信号
        delay_us(2);     // 保持 2us
        DS18B20_OUT_H(); // 释放总线，让 DS18B20 接管
        delay_us(10);    // 在 15us 内读取总线状态是最佳时机
        
        if (DS18B20_IN() == GPIO_PIN_SET) {
            data |= 0x80; // 如果总线为高，记录 1 (放到最高位，循环右移后会到正确位置)
        }
        delay_us(50);     // 等待读时隙结束 (总共需 60us)
    }
    return data;
}

// ====================================================================
// 顶层应用接口 (专为异步状态机设计)
// ====================================================================

/**
  * @brief  等待温度转换完成（读取总线电平判断）
  * @param  timeout_ms 最大等待时间（毫秒）
  * @retval 1: 完成; 0: 超时
  */
uint8_t DS18B20_WaitForConversion(uint32_t timeout_ms) {
    uint32_t start = HAL_GetTick();
    while ((HAL_GetTick() - start) < timeout_ms) {
        if (DS18B20_IN() == GPIO_PIN_SET) {
            return 1; // 总线拉高表示转换完成
        }
    }
    return 0;
}


/**
  * @brief  初始化 DS18B20 环境
  * @retval 1: 成功; 0: 失败
  */
uint8_t DS18B20_Init(void) {
    DWT_Delay_Init(); // 初始化内核微秒定时器
    DS18B20_OUT_H();  // 确保初始状态总线为高电平
    return DS18B20_Reset(); 
}

/**
  * @brief  [非阻塞] 下发温度转换指令，立刻返回，不等待 750ms
  */
void DS18B20_StartConvert(void) {
    if (DS18B20_Reset()) {
        DS18B20_WriteByte(0xCC); // 发送 Skip ROM 指令 (仅接一个传感器时适用)
        DS18B20_WriteByte(0x44); // 发送 Convert T 指令 (开始测温)
    }
}

/**
  * @brief  [非阻塞] 读取传感器温度并直接返回整型温度（摄氏度）
  * @retval uint8 温度整数值（0~255）；掉线或负温统一返回 0
  */
uint8_t DS18B20_ReadTemp(void) {
    uint8_t temp_L, temp_H;
    int16_t raw_temp;

    if (!DS18B20_Reset()) {
        return 0; // 掉线
    }

    DS18B20_WriteByte(0xCC); // Skip ROM
    DS18B20_WriteByte(0xBE); // Read Scratchpad

    temp_L = DS18B20_ReadByte();
    temp_H = DS18B20_ReadByte();

    // 原始值为 1/16°C 定点数，直接取整摄氏度：raw_temp / 16
    raw_temp = (int16_t)((temp_H << 8) | temp_L);

    if (raw_temp <= 0) {
        return 0;
    }

    raw_temp = (int16_t)(raw_temp >> 4);
    if (raw_temp > 255) {
        raw_temp = 255;
    }

    return (uint8_t)raw_temp;
}
