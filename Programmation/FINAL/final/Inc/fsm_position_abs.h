#ifndef FSM_POSITION_ABS_H
#define FSM_POSITION_ABS_H

#include "fsm_master.h"
#include "Robotronik_corp_pid.h"
#include "odometry.h"
#include "machineEtat.h"



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
int ramp_generator(int goal, int start, int *nactual,int ntime);

#endif
