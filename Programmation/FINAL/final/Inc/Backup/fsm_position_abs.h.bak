#ifndef FSM_POSITION_ABS_H
#define FSM_POSITION_ABS_H

#include "fsm_master.h"
#include "Robotronik_corp_pid.h"
#include "odometry.h"

typedef struct FSM_Position_Abs_S{
  FSM_Instance instance;
  float angle;//in rad
  float pos;//in mm
  float linear_speed;//in cm/s
  float angular_speed;//in rad/s
  float x;
  float y;
  int n;
  int initial_sum;
}FSM_Position_Abs;

void FSM_Pos_Init(FSM_Instance*);
void FSM_Angle_Init(FSM_Instance*);
void FSM_Pos_Generator(FSM_Instance*);
void FSM_Angle_Generator(FSM_Instance*);
void FSM_Pos_Wait(FSM_Instance*);
void FSM_Angle_Wait(FSM_Instance*);
void FSM_Abs_End(FSM_Instance*);

void FSM_X_Y_Init(FSM_Instance*);
void FSM_Angle_Init_X_Y(FSM_Instance*);
void FSM_Angle_Generator_X_Y(FSM_Instance *fsm);
void FSM_Angle_Wait_X_Y(FSM_Instance *fsm);
void FSM_Pos_Init_X_Y(FSM_Instance *fsm);
void FSM_Pos_Generator_X_Y(FSM_Instance *fsm);
void FSM_Pos_Wait_X_Y(FSM_Instance *fsm);

#endif
