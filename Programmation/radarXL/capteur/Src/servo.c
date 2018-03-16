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
  for (i=0; i<*nbServos;i++){
    XL_Say_Hello(&servo[i]);
    HAL_Delay(100);
    XL_Power_On(&servo[i], XL_NOW);
  }
}

void AngleVariation(XL* servo, int* angle, int pas, int maxAngle, int* sens){
  if (*sens){
    if(*angle<maxAngle){
      XL_Set_Goal_Position(servo, *angle, 1);
      *angle+=pas;
    }
    else
      *sens = 0;
  }
  else{
    if(*angle>=0){
      XL_Set_Goal_Position(servo, *angle, 1);
      *angle-=pas;
    }
    else
      *sens = 1;
  }
}

void AngleTransmit(XL* servo, int* ptr_angle, char* buffer, int* i, int* sens){ ///test fonctionne
		uint16_t position;
		char dataAngle[10];
		char ligne[2];
		int len;
		AngleVariation(&servo[0], ptr_angle, 30, 1000, sens);
		/*HAL_Delay(1000);
		XL_Get_Current_Position(&servo, &position);   /////test fonctionne Db=115200
		sprintf(dataAngle, "%d,",position);
		len=strlen(dataAngle);
		HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000); */
		HAL_Delay(10);
		XL_Get_Current_Position(servo, &position);
		HAL_Delay(10);
    if (*i<10-1){                 /////ajout valeur, dans data
        sprintf(dataAngle, "%d,",position);
        /*len=strlen(dataAngle);
        HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
    }  else if (*i==10-1){           /////ajout valeur dans data -> pour cloturer la sequence
        sprintf(dataAngle, "%d",position);
        /*len=strlen(dataAngle);
        HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
    }
    strcat(buffer,dataAngle);                          /////ajout valeur au buffer
    if (*i==10-1){
        len=strlen(buffer);                       /////longueur du buffer
        HAL_UART_Transmit(&huart2, (uint8_t*)(buffer), len, 1000); /////transmission du buffer
        sprintf(ligne, "\n");                                     /////ajout \n a ligne
        HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne
        (*i)=-1;                                                  /////remise a zero du compteur
        sprintf(buffer, "");                                      /////remise a zero du buffer
        HAL_Delay(1000);         //////necessaire pour le graphique
    }
}
