#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "xl_320.h"

//printf("0x%2.2X");
//scanf("%x",&byte);

void set_direction(){

}

uint32_t get_tick(){
  return 0;
}

uint8_t receive(uint8_t *data, uint16_t size, uint32_t timeout){
  while(size){
    scanf("%x", data++);
    size--;
  }
  return 0;
}

int main(){
  XL_Interface interface;
  interface.receive = receive;
  interface.set_direction = set_direction;
  
  XL_Status_Packet status_packet;
  if(XL_Receive(&interface, 14, 1)){
    printf("Erreur");
    return EXIT_SUCCESS;
  }

  printf("\n");
  printf("ID : 0x%2.2X\n", status_packet.id);
  printf("Err : 0x%2.2X\n", status_packet.err);
  printf("Nb_params : 0x%2.2X\n", status_packet.nb_params);
  printf("params : ");
  int i = 0;
  for(i = 0; i < status_packet.nb_params; i++){
    printf("0x%2.2X ", status_packet.params[i]);
  }
  printf("\n");
  
  return EXIT_SUCCESS;
}
