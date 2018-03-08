#include <stdio.h>
#include "xl_320.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart1;

#define USART1_DIR_Pin GPIO_PIN_9
#define USART1_DIR_GPIO_Port GPIOC

uint8_t XL_320_Send_HAL(uint8_t*, uint16_t, uint32_t);
void XL_320_Set_Direction_HAL(XL_Direction);
uint8_t XL_320_Receive_HAL(uint8_t*, uint16_t, uint32_t);
void XL_320_Delay_HAL(uint32_t);
void XL320InterfaceDefine(XL_Interface*);
void XL320ServosActivation(XL_Interface*, XL*, uint8_t, uint16_t*);