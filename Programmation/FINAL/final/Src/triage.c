
#include "triage.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "xl_320.h"
#include "lancer.h"
#include "deplacement.h"

void InitialisationServo(MachineEtat* machineEtat){
    ControlePorteEntree(machineEtat, -1);
    ControleSortieBalle(machineEtat, -1);
    ControleAccelerateur(machineEtat, -1);
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

int ReceptionArduinoCouleur(GPIO_TypeDef* portArduino, uint16_t pinArduino, int* couleurDetecte){
    *couleurDetecte = HAL_GPIO_ReadPin(portArduino, pinArduino);
    return *couleurDetecte;
}

/*void TestFinTri(MachineEtat* machineEtat, GPIO_TypeDef* portArduino, uint16_t pinArduino){
    if (((machineEtat->triage).secouer > (machineEtat->triage).secouerPrecedent || (machineEtat->triage).nombreBallesDetectees == 8 + (machineEtat->triage).nombreBallesTri1) && ReceptionArduinoCouleur(portArduino, pinArduino)==0){
        (machineEtat->triage).tri++;
    }
    if ((machineEtat->triage).nombreBallesDetectees == 8 + (machineEtat->triage).nombreBallesTri1 && ReceptionArduinoCouleur(portArduino, pinArduino, &((machineEtat->triage).couleurDetecte))==0){
        (machineEtat->triage).tri++;
    }
}*/

void Tri(MachineEtat* machineEtat, GPIO_TypeDef* portArduino, uint16_t pinArduino){
    while ((machineEtat->triage).tri<=(machineEtat->triage).triPrecedent){
        switch (ReceptionArduinoCouleur(portArduino, pinArduino, &((machineEtat->triage).couleurDetecte))){
            /*case 0:
                secouer(machineEtat);
                HAL_Delay(1000);
                if(ReceptionArduinoCouleur(portArduino, pinArduino, &((machineEtat->triage).couleurDetecte))==0){
                    break;
                }*/
            default:
                if ((machineEtat->triage).couleurDetecte == (machineEtat->triage).maCouleur){
                    HAL_Delay(10000);
                    ControleSortieBalle(machineEtat, -1);
                    HAL_Delay(50);
                    ControlePorteEntree(machineEtat, 1);
                    HAL_Delay(825);
                    ControlePorteEntree(machineEtat,-1);
                    HAL_Delay(1200);
                    AccelerateurBalle(machineEtat);
                    HAL_Delay(50);
                }
                else if((machineEtat->triage).couleurDetecte == -(machineEtat->triage).maCouleur){
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
                    ControleSortieBalle(machineEtat, 1);
                    HAL_Delay(50);
                    ControlePorteEntree(machineEtat, 1);
                    HAL_Delay(600);
                    ControlePorteEntree(machineEtat, -1);
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
                }
                break;
        }
        //TestFinTri(machineEtat, portArduino, pinArduino);
    }
}