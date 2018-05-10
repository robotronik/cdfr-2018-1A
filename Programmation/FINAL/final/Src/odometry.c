#include "odometry.h"

volatile float ENCODER_DIST=190.66;//distance between encoders
//attention jai mis un fois 2 pourcompenser le nb dimpulsions
volatile float ENCODER_STEP_DIST=2*20.65*2*M_PI/1440.0; //distance for 1 encoder step SAME
volatile float deltaL=(2.27799*2*20.65*2*M_PI/1440.0)/199.66; //ENCODER_STEP_DIST/ENCODER_DIST
int i;

void update_odometry(Odometry *odometry){
  int dl_l = update_encoder(&odometry->encoder_l);
  int dl_r = update_encoder(&odometry->encoder_r);
  if(i%100000==0){
    //debugline
    i=1;
  }i++;
#if TEST_ENCODER==1
  led_level = (int) (((float) odometry->encoder_l.htim->Instance->CNT / ENCODER_MAX)*255);
#endif

#if TEST_ENCODER==2
  led_level = (int) (((float) odometry->encoder_r.htim->Instance->CNT / ENCODER_MAX)*255);
#endif


  odometry->x = odometry->x
    + cos(odometry->theta)*ENCODER_STEP_DIST*(dl_l + dl_r);

  odometry->y = odometry->y
    + sin(odometry->theta)*ENCODER_STEP_DIST*(dl_l + dl_r);

  odometry->theta = odometry->theta+deltaL*(dl_l - dl_r);

  if(odometry->theta>PI)//angle limitation to -PI +PI
  {
    odometry->theta=odometry->theta-2*PI;
  }
  else if(odometry->theta<=-PI)
  {
    odometry->theta=odometry->theta+2*PI;
  }
}

void init_odometry(Odometry *odometry, TIM_HandleTypeDef *htim_poll){
  odometry->x = odometry->y = 0;
  odometry->theta = 0;
  i=0;

  init_encoder(&odometry->encoder_l);
  init_encoder(&odometry->encoder_r);

  start_encoder(&odometry->encoder_l);
  start_encoder(&odometry->encoder_r);

  HAL_TIM_Base_Start_IT(htim_poll);
}
