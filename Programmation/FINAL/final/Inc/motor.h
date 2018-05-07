#ifndef MOTOR_H
#define MOTOR_H

#define PWM_MAX 50 //a value between 0 and 255, 255 if not for debug

#define DRIVE_MOTOR(voltage, side_port, side_pin, fwd_state, tim_channel) {	\
  int16_t value = (int16_t) (voltage * (255.0 / 12.0));		\
  									\
  if(voltage > 0){							\
    HAL_GPIO_WritePin(side_port, side_pin, fwd_state);	\
  }									\
  else{									\
    HAL_GPIO_WritePin(side_port, side_pin, (~fwd_state)&1);		\
    value = -value;							\
  }									\
									\
  if(value > PWM_MAX) value = PWM_MAX;					\
  sConfigOC.Pulse = value;						\
  									\
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, tim_channel); \
  HAL_TIM_PWM_Start(&htim3, tim_channel);			\
  }

#define DRIVE_MOTOR_R(voltage) DRIVE_MOTOR(voltage, DIR_R_GPIO_Port, DIR_R_Pin, 1, TIM_CHANNEL_1);
#define DRIVE_MOTOR_L(voltage) DRIVE_MOTOR(voltage, DIR_L_GPIO_Port, DIR_L_Pin, 0, TIM_CHANNEL_2);

#endif
