#ifndef SERVO_H
#define SERVO_H

#include <stdio.h>
#include "xl_320.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

uint8_t XL_320_Send_HAL(uint8_t *data, uint16_t size, uint32_t timeout);
void XL_320_Set_Direction_HAL(XL_Direction dir);
uint8_t XL_320_Receive_HAL(uint8_t *buffer, uint16_t size, uint32_t timeout);
void XL_320_Delay_HAL(uint32_t t);
void XL320InterfaceDefine(XL_Interface* interface);
void XL320ServosActivation(XL_Interface* interface, XL* servo, uint8_t nbmServosWanted, uint16_t* nbServos);
void angle_variation(XL* servo, int pas, int* sens);

#endif