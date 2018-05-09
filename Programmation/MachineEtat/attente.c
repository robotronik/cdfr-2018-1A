#include "attente.h"

void Pause(MachineEtat* machineEtat){
    HAL_Delay((machineEtat->attente).deltaT);
    finAttente = 1;
}