#include "deplacement.h"
#include "motor.h"
#include "tim.h"

//extern MachineEtat machineEtat;

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
  Avancer(machineEtat); // ici la strategie
}

float cor_sum, cor_diff,val_r,val_l;
// cest degeux parce que j'ai copié les macros
void Avancer(MachineEtat* machineEtat){
    (machineEtat->deplacement).asserv.fsm_pos.instance.run(&((machineEtat->deplacement).asserv.fsm_pos.instance));
  //Process PID
    cor_sum = pid(&((machineEtat->deplacement).asserv.pid_sum),
                  (machineEtat->deplacement).asserv.sum_goal
                  - 0.5 * ((machineEtat->deplacement).odometrie.encoder_l.steps + (machineEtat->deplacement).odometrie.encoder_r.steps));
    cor_diff = pid(&((machineEtat->deplacement).asserv.pid_diff),
                  (machineEtat->deplacement).asserv.diff_goal
                  - ((machineEtat->deplacement).odometrie.encoder_r.steps - (machineEtat->deplacement).odometrie.encoder_l.steps));

    val_r = cor_sum + cor_diff;
    val_l = cor_sum - cor_diff;
    //SET_MOTOR_R(val_r); -----------------------------LOL
    int16_t value = (int16_t) (val_r *(255.0/voltMax));
    if (val_r >0){
      (machineEtat->deplacement).moteurDroit.superPin.pin = RD_av_Pin;
      (machineEtat->deplacement).moteurDroit.superPin.type = RD_av_GPIO_Port;
      HAL_GPIO_WritePin(RD_ar_GPIO_Port,RD_ar_Pin,0);
    }
    else{
      (machineEtat->deplacement).moteurDroit.superPin.pin = RD_ar_Pin;
      (machineEtat->deplacement).moteurDroit.superPin.type = RD_ar_GPIO_Port;
      HAL_GPIO_WritePin(RD_av_GPIO_Port,RD_av_Pin,0);
      value =-value;
    }
    if (value > PWM_MAX){
      value = PWM_MAX;
    }
    else if (!value){
      sConfigOC.Pulse = 1;
    }
    else {
      sConfigOC.Pulse = value;
    }
    HAL_TIM_PWM_ConfigChannel(&htim1,&sConfigOC,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    //SET_MOTOR_L(val_l); --------------------------------
     value = (int16_t) (val_l *(255.0/voltMax));
    if (val_l >0){
      (machineEtat->deplacement).moteurGauche.superPin.pin = RG_ar_Pin;
      (machineEtat->deplacement).moteurGauche.superPin.type = RG_ar_GPIO_Port;
      HAL_GPIO_WritePin(RG_av_GPIO_Port,RG_av_Pin,0);
    }
    else{
      (machineEtat->deplacement).moteurGauche.superPin.pin = RG_av_Pin;
      (machineEtat->deplacement).moteurGauche.superPin.type = RG_av_GPIO_Port;
      HAL_GPIO_WritePin(RG_ar_GPIO_Port,RG_ar_Pin,0);

      value =-value;
    }
    if (value > PWM_MAX){
      value = PWM_MAX;
    }
    else if (!value){
      sConfigOC.Pulse = 1;
    }
    else {
      sConfigOC.Pulse = value;
    }
    HAL_TIM_PWM_ConfigChannel(&htim2,&sConfigOC,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_Delay((machineEtat->deplacement).asserv.Te);
}

void Tourner(int sens){
  if (sens) { /* Tourner a gauche */
    SET_MOTOR_L(5);
    SET_MOTOR_R(5);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  } else { /* Tourner a droite */ //lol cest trop bidon
    SET_MOTOR_L(-5);
    SET_MOTOR_R(-5);
    /* l'arreter lorsqu'on est dans le bon axe avec l'odometrie et un timer*/

  }
}
