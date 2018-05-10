#include "lancer.h"

void AccelerateurBalle(MachineEtat* machineEtat){
    if ((machineEtat->lancer).tir){
        ControleAccelerateur(machineEtat, 1);
        HAL_Delay(100);
        ControleAccelerateur(machineEtat, 1);
        (machineEtat->lancer).tir = 0;
    }
}

void ControleAccelerateur(MachineEtat* machineEtat, int sens){
    uint16_t pos;

    if (sens==0) {  pos = (machineEtat->triage).servosGlobal.positionAccelerateur.ferme;}
    else{ pos = (machineEtat->triage).servosGlobal.positionAccelerateur.ouvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).servosGlobal.servo[1]) , pos, 1);
}

void ActivationMoteur(){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

void EteintMoteur(){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
}