#include "attente.h"

void Pause(MachineEtat* machineEtat){
    HAL_Delay((machineEtat->attente).deltaT);
    (machineEtat->attente).finAttente = 1;
}

void ArretUltrason(MachineEtat* machineEtat){
    MoteurOff(&(machineEtat->deplacement).moteurGauche);
    MoteurOff(&(machineEtat->deplacement).moteurDroit);
    while((machineEtat->deplacement).detectionCapteur.detection){
    }
    HAL_GPIO_WritePin(GPIOA, LD2_Pin,0);
    (machineEtat->attente).finAttente = 1;
}