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

void ArretFinal(){
    MoteurOff();
    __disable_irq();
    while(1){
      MoteurOff();
    }
}