#ifndef FSM_MASTER_H
#define FSM_MASTER_H

#include "stm32f4xx_hal.h"

typedef enum FSM_Status_E{
  FSM_RUNNING,
  FSM_SUCCESS,
  FSM_ERROR
}FSM_Status;

typedef enum FSM_Error_E{
  ERR_AX_LINK,
  ERR_Z_GOAL,
}FSM_Error;

struct FSM_Instance_S;
typedef void (*FSM_Procedure)(struct FSM_Instance_S*);

typedef struct FSM_Instance_S{
  FSM_Procedure run;
  FSM_Status status;
  uint32_t time_limit;
}FSM_Instance;

#define FSM_SET_TIME_BUDGET(p_instance, t_ms) {p_instance->time_limit = HAL_GetTick() + t_ms;}
#define FSM_TIMEOUT_REACHED(p_instance) (HAL_GetTick() > p_instance->time_limit)
#define FSM_NEXT(p_instance, next_state, t_ms) {p_instance->run = next_state; FSM_SET_TIME_BUDGET(p_instance, t_ms);}


#endif
