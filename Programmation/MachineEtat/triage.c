
#include "triage.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "xl_320.h"


void ControlePorteEntree(MachineEtat* machineEtat, int ouverture){
    if (ouverture==0) { uint16_t pos =(machineEtat->triage).xl_porte_entre.posFerme;}
    else{ (machineEtat->triage).xl_porte_entre.posOuvert;}
    XL_Set_Goal_Position((machineEtat->triage).xl_porte_entre.servo, , uint8_t now);
}
