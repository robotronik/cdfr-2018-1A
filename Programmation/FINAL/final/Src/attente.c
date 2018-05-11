#include "attente.h"

void Pause(MachineEtat* machineEtat){
    HAL_Delay((machineEtat->attente).deltaT);
    (machineEtat->attente).finAttente = 1;
}

void ArretUltrason(MachineEtat* machineEtat){
    MoteurOff();
    while((machineEtat->deplacement).detectionCapteur.detection){
    }
    (machineEtat->attente).finAttente = 1;
}

void FinDuMatch(MachineEtat* machineEtat){
    __disable_irq();
    MoteurOff();
    while(1){
        HAL_Delay(1000);
    }
}
