#include "relay_control.h"

// 1. 发送继电器 (高电平打开)
void TXrelayOn(void)  { HAL_GPIO_WritePin(RELAY_TX_CTRL_GPIO_Port, RELAY_TX_CTRL_Pin, GPIO_PIN_SET); }
void TXrelayOff(void) { HAL_GPIO_WritePin(RELAY_TX_CTRL_GPIO_Port, RELAY_TX_CTRL_Pin, GPIO_PIN_RESET); }

// 2. 接收继电器 (低电平打开)
void RXrelayOn(void)  { HAL_GPIO_WritePin(RELAY_RX_CTRL_GPIO_Port, RELAY_RX_CTRL_Pin, GPIO_PIN_RESET); }
void RXrelayOff(void) { HAL_GPIO_WritePin(RELAY_RX_CTRL_GPIO_Port, RELAY_RX_CTRL_Pin, GPIO_PIN_SET); }

// 3. 功率放大器 AP (低电平使能)
void APon(void)       { HAL_GPIO_WritePin(AP_MUTE_CTRL_GPIO_Port, AP_MUTE_CTRL_Pin, GPIO_PIN_RESET); }
void APoff(void)      { HAL_GPIO_WritePin(AP_MUTE_CTRL_GPIO_Port, AP_MUTE_CTRL_Pin, GPIO_PIN_SET); }
