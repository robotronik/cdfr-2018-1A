#include "deplacement.h"

void Initialisation(MachineEtat* machineEtat, GPIO_TypeDef* RG_av_PORT, uint16_t RG_av_PIN, GPIO_TypeDef* RG_ar_PORT, uint16_t RG_ar_PIN, GPIO_TypeDef* RD_av_PORT, uint16_t RD_av_PIN, GPIO_TypeDef* RD_ar_PORT, uint16_t RD_ar_PIN){
  (machineEtat->deplacement).moteurGauche.av.type = RG_av_PORT;
  (machineEtat->deplacement).moteurGauche.av.pin = RG_av_PIN;
  (machineEtat->deplacement).moteurGauche.ar.type = RG_ar_PORT;
  (machineEtat->deplacement).moteurGauche.ar.pin = RG_ar_PIN;
  (machineEtat->deplacement).moteurDroit.av.type = RD_av_PORT;
  (machineEtat->deplacement).moteurDroit.av.pin = RD_av_PIN;
  (machineEtat->deplacement).moteurDroit.ar.type = RD_ar_PORT;
  (machineEtat->deplacement).moteurDroit.ar.pin = RD_ar_PIN;
}

void MoteurAvant(Moteur* moteur){
  HAL_GPIO_WritePin(moteur->av.type, moteur->av.pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(moteur->ar.type, moteur->ar.pin, GPIO_PIN_RESET);
}

void MoteurOff(Moteur* moteur){
  HAL_GPIO_WritePin(moteur->av.type, moteur->av.pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(moteur->ar.type, moteur->ar.pin, GPIO_PIN_RESET);
}

void DeplacementGlobal(MachineEtat* machineEtat){
  Avancer(machineEtat);
}

void Avancer(MachineEtat* machineEtat){
  MoteurAvant(&((machineEtat->deplacement).moteurGauche));
  MoteurAvant(&((machineEtat->deplacement).moteurDroit));
  /*  A completer avec l'odometrie  */



}

void Tourner(MachineEtat* machineEtat, int sens){
  if (sens) { /* Tourner a gauche */
    MoteurOff(&((machineEtat->deplacement).moteurGauche));
    MoteurAvant(&((machineEtat->deplacement).moteurDroit));
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  } else { /* Tourner a droite */
    MoteurOff(&((machineEtat->deplacement).moteurDroit));
    MoteurAvant(&((machineEtat->deplacement).moteurGauche));
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  }
}