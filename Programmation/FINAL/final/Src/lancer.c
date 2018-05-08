#include "lancer.h"

void AccelerateurBalle(MachineEtat* machineEtat){
    if ((machineEtat->lancer).tir){
        HAL_Delay(1000);
        XL_Set_Goal_Position( &((machineEtat->lancer).accelerateur.servo), (machineEtat->lancer).accelerateur.posFerme, 1);
        HAL_Delay(10);
        XL_Set_Goal_Position( &((machineEtat->lancer).accelerateur.servo), (machineEtat->lancer).accelerateur.posOuvert, 1);
        (machineEtat->lancer).tir = 0;
        TransitionEtats(machineEtat);
    }
}

void ActivationMoteur(){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}