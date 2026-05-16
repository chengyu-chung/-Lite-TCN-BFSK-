#include "relay_control.h"

// 1. 发送继电器控制 (TX Relay) - 高电平有效 (高电平闭合)
void TXrelayOn(void)  { HAL_GPIO_WritePin(RELAY_TX_CTRL_GPIO_Port, RELAY_TX_CTRL_Pin, GPIO_PIN_SET); }   // 输出高，继电器闭合，使能发送
void TXrelayOff(void) { HAL_GPIO_WritePin(RELAY_TX_CTRL_GPIO_Port, RELAY_TX_CTRL_Pin, GPIO_PIN_RESET); } // 输出低，继电器断开，禁止发送

// 2. 接收继电器控制 (RX Relay) - 低电平有效 (低电平闭合)
void RXrelayOn(void)  { HAL_GPIO_WritePin(RELAY_RX_CTRL_GPIO_Port, RELAY_RX_CTRL_Pin, GPIO_PIN_RESET); } // 输出低，继电器闭合，使能接收
void RXrelayOff(void) { HAL_GPIO_WritePin(RELAY_RX_CTRL_GPIO_Port, RELAY_RX_CTRL_Pin, GPIO_PIN_SET); }   // 输出高，继电器断开，禁止接收

// 3. 功放使能控制 (AP Mute) - 低电平有效 (低电平开启功放)
void APon(void)       { HAL_GPIO_WritePin(AP_MUTE_CTRL_GPIO_Port, AP_MUTE_CTRL_Pin, GPIO_PIN_RESET); } // 输出低，解除静音，功放工作
void APoff(void)      { HAL_GPIO_WritePin(AP_MUTE_CTRL_GPIO_Port, AP_MUTE_CTRL_Pin, GPIO_PIN_SET); }   // 输出高，开启静音，功放关闭
