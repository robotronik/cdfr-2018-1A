
#include "triage.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "xl_320.h"

// TODO : voir pour un get pos apres les goal pos
void ControlePorteEntree(MachineEtat* machineEtat, int ouverture){
    uint16_t pos;

    if (ouverture==0) {  pos = (machineEtat->triage).xl_porte_entre.posFerme;}
    else{ pos = (machineEtat->triage).xl_porte_entre.posOuvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).xl_porte_entre.servo) , pos, 1);
}

void ControleSortieBalle(MachineEtat* machineEtat,int sens){
    uint16_t pos;

    if (sens==0) {  pos = (machineEtat->triage).xl_porte_sortie.posFerme;}
    else{ pos = (machineEtat->triage).xl_porte_sortie.posOuvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).xl_porte_sortie.servo) , pos, 1);
}

char ReceptionArduinoCouleur(UART_HandleTypeDef* huart){
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
}

void TestFinTri(MachineEtat* machineEtat){
    if ((machineEtat->triage).secouer > (machineEtat->triage).secouerPrecedent || (machineEtat->triage).nombreBallesDetectees == 8 + (machineEtat->triage).nombreBallesTri1){
        (machineEtat->triage).tri++;
    }
}