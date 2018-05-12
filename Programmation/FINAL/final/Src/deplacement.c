#include "deplacement.h"
#include "motor.h"


TIM_OC_InitTypeDef sConfigOC = {.OCMode = TIM_OCMODE_PWM1, .OCPolarity = TIM_OCPOLARITY_HIGH, .OCFastMode = TIM_OCFAST_DISABLE};

/* Initialisation sans macro */
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

void MoteurOff(){
  SET_MOTOR_L(-0.0);
  SET_MOTOR_R(0.0);
}

void DeplacementGlobal(MachineEtat* machineEtat){
  Avancer();
}

void Avancer(){
  SET_MOTOR_L(4.0);
  SET_MOTOR_R(5.0);
  /*  A completer avec l'odometrie  */



}

void Tourner(int sens){
  if (sens) { /* Tourner a gauche */
    SET_MOTOR_L(-7);
    SET_MOTOR_R(-7);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  } else { /* Tourner a droite */ //lol cest trop bidon
    SET_MOTOR_L(-5);
    SET_MOTOR_R(-5);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  }
}
