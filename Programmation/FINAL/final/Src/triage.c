
#include "triage.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "xl_320.h"
#include "lancer.h"

void InitialisationServo(MachineEtat* machineEtat){
    ControlePorteEntree(machineEtat, 0);
    ControleSortieBalle(machineEtat, 0);
    ControleAccelerateur(machineEtat, 0);
}

// TODO : voir pour un get pos apres les goal pos
void ControlePorteEntree(MachineEtat* machineEtat, int sens){
    uint16_t pos;

    if (sens==0) {  pos = (machineEtat->triage).servosGlobal.positionPorteEntree.ferme;}
    else{ pos = (machineEtat->triage).servosGlobal.positionPorteEntree.ouvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).servosGlobal.servo[0]) , pos, 1);
}

void ControleSortieBalle(MachineEtat* machineEtat,int sens){
    uint16_t pos;

    if (sens==0) {  pos = (machineEtat->triage).servosGlobal.positionPorteSortie.ferme;}
    else{ pos = (machineEtat->triage).servosGlobal.positionPorteSortie.ouvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).servosGlobal.servo[2]), pos, 1);
}

char ReceptionArduinoCouleur(UART_HandleTypeDef* huart){
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
}

void TestFinTri(MachineEtat* machineEtat){
    if ((machineEtat->triage).secouer > (machineEtat->triage).secouerPrecedent || (machineEtat->triage).nombreBallesDetectees == 8 + (machineEtat->triage).nombreBallesTri1){
        (machineEtat->triage).tri++;
    }
}

void Tri(MachineEtat* machineEtat){

}