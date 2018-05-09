#include "encoder.h"

#if TEST_ENCODER != 0
uint8_t led_level;
#endif

void init_encoder(Encoder *encoder /*  TIM_HandleTypeDef *htima*/){
  encoder->last_pos = encoder->steps = 0;
  encoder->cmpt = 0;
  //encoder -> htima = htima; lol
}

int update_encoder(Encoder *encoder){
  const int cnt = encoder->cmpt; //mettre adiition des deux htim #sale genre :
  //cnt+=encoder->htima-> Instance -> CNT;

  int dl = cnt - encoder->last_pos;
  encoder->last_pos = cnt; //apres ca je sais pas wallah inchalla
  if(dl > 1){
    dl = -1;
  }else if(dl < -1){
    dl = +1;
  }
  
  encoder->steps += dl;

  return dl;
}

void start_encoder(Encoder *encoder){
  // tu n'as pas besoin de htim quand tu es dans la matrix et que tu simule le htim
  //HAL_TIM_Encoder_Start(encoder->htim, TIM_CHANNEL_ALL);
}
