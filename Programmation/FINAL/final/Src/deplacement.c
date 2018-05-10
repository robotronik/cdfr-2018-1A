#include "deplacement.h"
#include "motor.h"


TIM_OC_InitTypeDef sConfigOC = {.OCMode = TIM_OCMODE_PWM1, .OCPolarity = TIM_OCPOLARITY_HIGH, .OCFastMode = TIM_OCFAST_DISABLE};


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
  SET_MOTOR_L(-5.0);
  SET_MOTOR_R(5.0);
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
/*
void setVoltageMoteur (Moteur* moteur , float voltage){ // prototype a verif
  int16_t value = (int16_t) (voltage *(255.0/12.0));
  TIM_OC_InitTypedef sConfigOC;
  //peut etre inclure .. quoi je ne sais plus  
  if (voltage >0){
    //set pwm à avant et 0 a l'autre .. alllez cest parrrtttti
    moteur->superPin = moteur->av;
    HAL_GPIO_WritePin((moteur->ar).type,(moteur->ar).pin,0);
  }
  else{
    //set pwm à arriere et 0 à l'autre
    moteur->superPin = moteur->ar;
    HAL_GPIO_WritePin((moteur->av).type,(moteur->av).pin,0);
    value =-value;
  }
  //check max value
  if (value > PWM_MAX){
    value = PWM_MAX;
  }
  sConfigOC.Pulse = value;
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  //a ajouter htim dans moteur struct et verifier vlue sconfig puis channel 1 cf cubeMX
  HAL_TIM_PWM_ConfigChannel(moteur->htim,&sConfigOC,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(moteur->htim, TIM_CHANNEL_1);
}*/