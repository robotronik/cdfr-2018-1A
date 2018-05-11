#include "fsm_position_abs.h"
//http://manubatbat.free.fr/doc/positionning/node5.html
extern MachineEtat machineEtat;
/*extern PID_DATA (machineEtat.deplacement).asserv.pid_sum;
extern PID_DATA (machineEtat.deplacement).asserv.pid_diff;
extern int (machineEtat.deplacement).asserv.sum_goal;
extern int (machineEtat.deplacement).asserv.diff_goal;
extern Odometry (machineEtat.deplacement).odometrie;
*/
extern volatile float ENCODER_DIST;//distance between encoders
extern volatile float ENCODER_STEP_DIST;//distance for 1 encoder step/2
extern volatile float deltaL;

void FSM_Pos_Init(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  fsm->status=FSM_RUNNING;
  fsm_pos->n=0;
  fsm_pos->initial_sum=(machineEtat.deplacement).asserv.sum_goal; //0 au dep
  fsm->run=FSM_Pos_Generator;
}

void FSM_Pos_Generator(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  if(fabsf(fsm_pos->pos/fsm_pos->linear_speed) >fsm_pos->n*(machineEtat.deplacement).asserv.pid_sum.Te)
  {
    (machineEtat.deplacement).asserv.sum_goal=fsm_pos->initial_sum+fsm_pos->n*fsm_pos->linear_speed*(machineEtat.deplacement).asserv.pid_sum.Te/ENCODER_STEP_DIST;
    fsm_pos->n++;
  }
  else
  {
    (machineEtat.deplacement).asserv.sum_goal=fsm_pos->initial_sum+(double) fsm_pos->pos / (double)ENCODER_STEP_DIST;
    fsm->run=FSM_Pos_Wait;
  }
}

void FSM_Pos_Wait(FSM_Instance *fsm)
{
  if(reached(&(machineEtat.deplacement).asserv.pid_sum,(machineEtat.deplacement).asserv.sum_goal- 0.5 * ((machineEtat.deplacement).odometrie.encoder_l.steps + (machineEtat.deplacement).odometrie.encoder_r.steps))) fsm->run=FSM_Abs_End;
}

void FSM_Abs_End(FSM_Instance *fsm)
{
  fsm->status=FSM_SUCCESS;
}

void FSM_Angle_Init(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  fsm->status=FSM_RUNNING;
  fsm_pos->n=0;
  fsm_pos->angle+=(machineEtat.deplacement).odometrie.theta;//no value limitation
  fsm->run=FSM_Angle_Generator;
}

void FSM_Angle_Generator(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  if(fabsf(fsm_pos->angle/fsm_pos->angular_speed) >fsm_pos->n*(machineEtat.deplacement).asserv.pid_diff.Te)
  {
    (machineEtat.deplacement).asserv.diff_goal=fsm_pos->n*fsm_pos->angular_speed*(machineEtat.deplacement).asserv.pid_diff.Te*ENCODER_DIST/ENCODER_STEP_DIST;
    fsm_pos->n++;
  }
  else
  {
    (machineEtat.deplacement).asserv.diff_goal=fsm_pos->angle*ENCODER_DIST/ENCODER_STEP_DIST;
    fsm->run=FSM_Angle_Wait;
  }
}

void FSM_Angle_Wait(FSM_Instance *fsm)
{
  if(reached(&(machineEtat.deplacement).asserv.pid_diff,(machineEtat.deplacement).asserv.diff_goal - ((machineEtat.deplacement).odometrie.encoder_r.steps - (machineEtat.deplacement).odometrie.encoder_l.steps))) fsm->run=FSM_Abs_End;
}





/********************
***   DIRTY ZONE  ***
********************/


void FSM_X_Y_Init(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  fsm_pos->angle=acos((((machineEtat.deplacement).odometrie.x*fsm_pos->x)+((machineEtat.deplacement).odometrie.y*fsm_pos->y))/
                  (sqrt(pow((machineEtat.deplacement).odometrie.x,2)+pow((machineEtat.deplacement).odometrie.y,2))+sqrt(pow(fsm_pos->x,2)+pow(fsm_pos->y,2))));
  fsm_pos->pos=sqrt(pow((machineEtat.deplacement).odometrie.x-fsm_pos->x,2)+pow((machineEtat.deplacement).odometrie.y-fsm_pos->y,2));
}

void FSM_Angle_Init_X_Y(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  fsm->status=FSM_RUNNING;
  fsm_pos->n=0;
  fsm_pos->angle+=(machineEtat.deplacement).odometrie.theta;//no value limitation
  fsm->run=FSM_Angle_Generator_X_Y;
}

void FSM_Angle_Generator_X_Y(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  if(fabsf(fsm_pos->angle/fsm_pos->angular_speed) >fsm_pos->n*(machineEtat.deplacement).asserv.pid_diff.Te)
  {
    (machineEtat.deplacement).asserv.diff_goal=fsm_pos->n*fsm_pos->angular_speed*(machineEtat.deplacement).asserv.pid_diff.Te*ENCODER_DIST/ENCODER_STEP_DIST;
    fsm_pos->n++;
  }
  else
  {
    (machineEtat.deplacement).asserv.diff_goal=fsm_pos->angle*ENCODER_DIST/ENCODER_STEP_DIST;
    fsm->run=FSM_Angle_Wait_X_Y;
  }
}

void FSM_Angle_Wait_X_Y(FSM_Instance *fsm)
{
  if(reached(&(machineEtat.deplacement).asserv.pid_diff,(machineEtat.deplacement).asserv.diff_goal - ((machineEtat.deplacement).odometrie.encoder_r.steps - (machineEtat.deplacement).odometrie.encoder_l.steps))) fsm->run=FSM_Pos_Init_X_Y;
}

void FSM_Pos_Init_X_Y(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  fsm->status=FSM_RUNNING;
  fsm_pos->n=0;
  fsm_pos->initial_sum=(machineEtat.deplacement).asserv.sum_goal;
  fsm->run=FSM_Pos_Generator_X_Y;
}

void FSM_Pos_Generator_X_Y(FSM_Instance *fsm)
{
  FSM_Position_Abs *fsm_pos=(FSM_Position_Abs *) fsm;
  if(fabsf(fsm_pos->pos/fsm_pos->linear_speed) >fsm_pos->n*(machineEtat.deplacement).asserv.pid_sum.Te)
  {
    (machineEtat.deplacement).asserv.sum_goal=fsm_pos->initial_sum+fsm_pos->n*fsm_pos->linear_speed*(machineEtat.deplacement).asserv.pid_sum.Te/ENCODER_STEP_DIST;
    fsm_pos->n++;
  }
  else
  {
    (machineEtat.deplacement).asserv.sum_goal=fsm_pos->initial_sum+fsm_pos->pos/ENCODER_STEP_DIST;
    fsm->run=FSM_Pos_Wait_X_Y;
  }
}

void FSM_Pos_Wait_X_Y(FSM_Instance *fsm)
{
  if(reached(&(machineEtat.deplacement).asserv.pid_sum,(machineEtat.deplacement).asserv.sum_goal- 0.5 * ((machineEtat.deplacement).odometrie.encoder_l.steps + (machineEtat.deplacement).odometrie.encoder_r.steps))) fsm->run=FSM_Abs_End;
}
