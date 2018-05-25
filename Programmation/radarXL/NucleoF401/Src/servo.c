#include "servo.h"
#include <string.h>
#include <stdlib.h>

uint8_t XL_320_Send_HAL(uint8_t *data, uint16_t size, uint32_t timeout){
  HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, data, size, timeout);
  return (status==HAL_OK)?0:1;
}

void XL_320_Set_Direction_HAL(XL_Direction dir){
  HAL_GPIO_WritePin(USART1_DIR_GPIO_Port, USART1_DIR_Pin, (dir==XL_SEND)?GPIO_PIN_SET:GPIO_PIN_RESET);
}

uint8_t XL_320_Receive_HAL(uint8_t *buffer, uint16_t size, uint32_t timeout){
  HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, buffer, size, timeout);
  return (status==HAL_OK)?0:1;
}

void XL_320_Delay_HAL(uint32_t t){
  HAL_Delay(t);
}

void XL320InterfaceDefine(XL_Interface* interface){
  interface->send = XL_320_Send_HAL;
  interface->set_direction = XL_320_Set_Direction_HAL;
  interface->receive = XL_320_Receive_HAL;
  interface->delay = XL_320_Delay_HAL;
}

void XL320ServosActivation(XL_Interface* interface, XL* servo, uint8_t nbmServosWanted, uint16_t* nbServos){
  int i;
  XL_Discover(interface, servo, nbmServosWanted, nbServos);
  HAL_Delay(10);
  for (i=0; i<*nbServos;i++){
    XL_Say_Hello(&servo[i]);
    HAL_Delay(100);
    XL_Power_On(&servo[i], XL_NOW);
  }
}

void angle_variation(XL* servo, int* angle, int pas, int maxAngle, int* sens){
  /* Increasing direction */
  if (*sens){
    if(*angle < maxAngle){
      XL_Set_Goal_Position(servo, *angle, 1);
      *angle += pas;
    }
    else
      *sens = 0;
  } /* Decreasing direction */
   else {
    if(*angle >= 0){
      XL_Set_Goal_Position(servo, *angle, 1);
      *angle -= pas;
    }
    else
      *sens = 1;
  }
}

void angle_transmit(XL* servo, int* ptr_angle, char* buffer, int* i, int* sens, int* ptr_rotation){
		uint16_t position;
		char dataAngle[10];
		char ligne[2];
		int len;
    if (*sens) {
      *ptr_rotation += DELTA_ANGLE;
    } else {
      *ptr_rotation -= DELTA_ANGLE;
    }

		angle_variation(&servo[0], ptr_angle, DELTA_ANGLE, 1023, sens);

    position = position*320/1023;
		HAL_Delay(10);
    if (*i < MAXI_CHAR){
          sprintf(dataAngle, "%d,", position);
    }  else if (*i == MAXI_CHAR){
          sprintf(dataAngle, "%d", position);
    }
    strcat(buffer, dataAngle);
}

void distance_transmit(int valeur, char* buffer, int* i){
		char data[10];
		char ligne[2];
		int len;
    if (*i < MAXI_CHAR){
        sprintf(data, "%d,", valeur);
    } else if (*i == MAXI_CHAR){
        sprintf(data, "%d|", valeur);
    }
    strcat(buffer, data);
}
