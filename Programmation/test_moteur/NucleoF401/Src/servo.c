#include "servo.h"
#include <string.h>
#include <stdlib.h>

uint8_t XL_320_Send_HAL(uint8_t *data, uint16_t size, uint32_t timeout){
  HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, data, size, timeout);
  return (status==HAL_OK)?0:1;
}

// void XL_320_Set_Direction_HAL(XL_Direction dir){
//   HAL_GPIO_WritePin(USART1_DIR_GPIO_Port, USART1_DIR_Pin, (dir==XL_SEND)?GPIO_PIN_SET:GPIO_PIN_RESET);
// }

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
  //HAL_Delay(10);
  //XL_Configure_Baud_Rate(servo, 2); ////warning
  //while(1)
  //{HAL_Delay(10);}
  for (i=0; i<*nbServos;i++){
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // HAL_Delay(100);
    XL_Say_Hello(&servo[i]);
    HAL_Delay(100);
    XL_Power_On(&servo[i], XL_NOW);
  }
}

void angle_variation(XL* servo, int pas, int* sens){
  uint16_t position;
  if (*sens) {
      XL_Set_Goal_Position(servo, pas, 1);
  } else {
      XL_Set_Goal_Position(servo, 0, 1);
  }
  HAL_Delay(10);
  XL_Get_Current_Position(servo, &position);
  HAL_Delay(10);
}
