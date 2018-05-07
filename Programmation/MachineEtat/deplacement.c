#include "deplacement.h"

void Initialisation(MachineEtat* machineEtat, Moteur* moteurGauche, Moteur* moteurDroit){
  *moteurGauche.av.type = GPIOB;
  *moteurGauche.av.pin = RG_av_Pin;
  *moteurGauche.ar.type = GPIOA;
  *moteurGauche.ar.pin = RG_ar_Pin;
  *moteurDroit.av.type = GPIOB;
  *moteurDroit.av.pin = RD_av_Pin;
  *moteurDroit.ar.type = GPIOB;
  *moteurDroit.ar.pin = RD_ar_Pin;
}

void MoteurAvant(Moteur moteur){
  HAL_GPIO_WritePin(moteur.av.type, moteur.av.pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(moteur.ar.type, moteur.ar.pin, GPIO_PIN_RESET);
}

void MoteurOff(Moteur moteur){
  HAL_GPIO_WritePin(moteur.av.type, moteur.av.pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(moteur.ar.type, moteur.ar.pin, GPIO_PIN_RESET);
}

void Deplacement(MachineEtat* machineEtat, Moteur* moteurGauche, Moteur* moteurDroit){
  MoteurAvant(moteurGauche);
  MoteurAvant(moteurDroit);
  /*  A completer avec l'odometrie  */



}

void Tourner(MachineEtat* machineEtat, Moteur* moteurGauche, Moteur* moteurDroit, int sens){
  if (sens) { /* Tourner a gauche */
    MoteurOff(moteurGauche);
    MoteurAvant(moteurDroit);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  } else { /* Tourner a droite */
    MoteurOff(moteurDroit);
    MoteurAvant(moteurGauche);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  }
}
