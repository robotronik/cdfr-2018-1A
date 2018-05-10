
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

    if (sens==-1) {  pos = (machineEtat->triage).servosGlobal.positionPorteEntree.ferme;}
    else{ pos = (machineEtat->triage).servosGlobal.positionPorteEntree.ouvert;}

    XL_Set_Goal_Position( &((machineEtat->triage).servosGlobal.servo[0]) , pos, 1);
}

void ControleSortieBalle(MachineEtat* machineEtat,int sens){
    uint16_t pos;

    if (sens==-1) {  pos = (machineEtat->triage).servosGlobal.positionPorteSortie.ferme;}
    else{ pos = (machineEtat->triage).servosGlobal.positionPorteSortie.ouvert;}
 
    XL_Set_Goal_Position( &((machineEtat->triage).servosGlobal.servo[2]), pos, 1);
}

int ReceptionArduinoCouleur(GPIO_TypeDef* portArduino, uint16_t pinArduino){
    return HAL_GPIO_ReadPin(portArduino, pinArduino);
}

void TestFinTri(MachineEtat* machineEtat){
    if ((machineEtat->triage).secouer > (machineEtat->triage).secouerPrecedent || (machineEtat->triage).nombreBallesDetectees == 8 + (machineEtat->triage).nombreBallesTri1){
        (machineEtat->triage).tri++;
    }
}

/*void Tri(MachineEtat* machineEtat, GPIO_TypeDef* portArduino, uint16_t pinArduino){
    while (ReceptionArduinoCouleur(portArduino, pinArduino)!=0){

    }
}*/