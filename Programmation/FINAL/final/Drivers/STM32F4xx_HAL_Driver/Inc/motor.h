#ifndef MOTOR_H
#define MOTOR_H

#define PWM_MAX 50

#define setVoltageMoteur (voltage, motavPort, motavPin, motarPort,motarPin,supPort,supPin,myhtim){ \
  int16_t value = (int16_t) (voltage *(255.0/12.0)); \
  if (voltage >0){\
    supPin = motavPin;\
    supPort = motavPort;\
    HAL_GPIO_WritePin(motarPort,motarPin,0);\
  }\
  else{\
    supPin = motarPin;\
    supPort = motarPort;\
    HAL_GPIO_WritePin(motavPort,motavPin,0);\
    value =-value; \
  }\
  if (value > PWM_MAX){\
    value = PWM_MAX;\
  }\
  sConfigOC.Pulse = value;\
HAL_TIM_PWM_ConfigChannel(&myhtim,&sConfigOC,TIM_CHANNEL_1);\
  HAL_TIM_PWM_Start(&myhtim, TIM_CHANNEL_1);\
}

#define SET_MOTOR_L(voltage) setVoltageMoteur(voltage, \
                                            RG_av_GPIO_Port,RG_ar_Pin,\
                                            RG_ar_GPIO_Port,RG_ar_Pin,\
                                            machineEtat.Deplacement.moteurGauche.superPin.type,\
                                            machineEtat.Deplacement.moteurGauche.superPin.pin,\
                                            htim2);
#define SET_MOTOR_R(voltage) setVoltageMoteur(voltage, \
                                            RD_av_GPIO_Port,RD_ar_Pin,\
                                            RD_ar_GPIO_Port,RD_ar_Pin,\
                                            machineEtat.Deplacement.moteurDroit.superPin.type,\
                                            machineEtat.Deplacement.moteurDroit.superPin.pin,\
                                            htim1);
#endif