#include "xl_320.h"
#include <stdio.h>

//========================================
//    CONSTANTES ET VARIABLES GLOBALES
//========================================
static const uint8_t header[4] = {0xFF, 0xFF, 0xFD, 0x00};
static const uint8_t stuffing_byte = 0xFD;
static const uint8_t field_addr[] = {
  [XL_ID] = 3,
  [XL_BAUD_RATE] = 4,
  [XL_RETURN_DELAY_TIME] = 5,
  [XL_CW_ANGLE_LIMIT] = 6,
  [XL_CCW_ANGLE_LIMIT] = 8,
  [XL_CONTROL_MODE] = 11,
  [XL_LIMIT_TEMPERATURE] = 12,
  [XL_LOWER_LIMIT_VOLTAGE] = 13,
  [XL_UPPER_LIMIT_VOLTAGE] = 14,
  [XL_MAX_TORQUE] = 15,
  [XL_RETURN_LEVEL] = 17,
  [XL_ALARM_SHUTDOWN] = 18,
  //EEPROM - Info
  [XL_MODEL_NUMBER] = 0,
  [XL_FIRMWARE_VERSION] = 2,
  //RAM - Contrôle
  [XL_TORQUE_ENABLE] = 24,
  [XL_LED] = 25,
  [XL_D_GAIN] = 27,
  [XL_I_GAIN] = 28,
  [XL_P_GAIN] = 29,
  [XL_GOAL_POSITION] = 30,
  [XL_MOVING_SPEED] = 32,
  [XL_TORQUE_LIMIT] = 35,
  [XL_PUNCH] = 51,
  //RAM - Info
  [XL_CURRENT_POSITION] = 37,
  [XL_CURRENT_SPEED] = 39,
  [XL_CURRENT_LOAD] = 41,
  [XL_CURRENT_VOLTAGE] = 45,
  [XL_CURRENT_TEMPERATURE] = 46,
  [XL_REGISTERED_INSTRUCTION] = 47,
  [XL_MOVING] = 49,
  [XL_HARDWARE_ERROR_STATUS] = 50,
};
static const uint8_t field_length[] = {
  [XL_ID] = 1,
  [XL_BAUD_RATE] = 1,
  [XL_RETURN_DELAY_TIME] = 1,
  [XL_CW_ANGLE_LIMIT] = 2,
  [XL_CCW_ANGLE_LIMIT] = 2,
  [XL_CONTROL_MODE] = 1,
  [XL_LIMIT_TEMPERATURE] = 1,
  [XL_LOWER_LIMIT_VOLTAGE] = 1,
  [XL_UPPER_LIMIT_VOLTAGE] = 1,
  [XL_MAX_TORQUE] = 2,
  [XL_RETURN_LEVEL] = 1,
  [XL_ALARM_SHUTDOWN] = 1,
  //EEPROM - Info
  [XL_MODEL_NUMBER] = 2,
  [XL_FIRMWARE_VERSION] = 1,
  //RAM - Contrôle
  [XL_TORQUE_ENABLE] = 1,
  [XL_LED] = 1,
  [XL_D_GAIN] = 1,
  [XL_I_GAIN] = 1,
  [XL_P_GAIN] = 1,
  [XL_GOAL_POSITION] = 2,
  [XL_MOVING_SPEED] = 2,
  [XL_TORQUE_LIMIT] = 2,
  [XL_PUNCH] = 2,
  //RAM - Info
  [XL_CURRENT_POSITION] = 2,
  [XL_CURRENT_SPEED] = 2,
  [XL_CURRENT_LOAD] = 2,
  [XL_CURRENT_VOLTAGE] = 1,
  [XL_CURRENT_TEMPERATURE] = 1,
  [XL_REGISTERED_INSTRUCTION] = 1,
  [XL_MOVING] = 1,
  [XL_HARDWARE_ERROR_STATUS] = 1,
};
static uint16_t err;

//========================================
//        FONCTIONS DE RECEPTION
//========================================
#define FSM_BYTE *(fsm->p_buffer)
#define FSM_NEXT fsm->p_buffer++
#define FSM_RESET fsm->update_state = XL_FSM_HEADER_0; fsm->p_buffer = fsm->buffer
#define FSM_UPDATE(state_function) fsm->update_state = state_function

void XL_FSM_HEADER_0(XL_Receiver_FSM *fsm){
  if(FSM_BYTE == header[0]){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_HEADER_1);
  }
}

void XL_FSM_HEADER_1(XL_Receiver_FSM *fsm){
  if(FSM_BYTE == header[1]){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_HEADER_2);
  }
  else{
    FSM_RESET;
  }
}

void XL_FSM_HEADER_2(XL_Receiver_FSM *fsm){
  if(FSM_BYTE == header[2]){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_HEADER_3);
  }
  else{
    FSM_RESET;
  }
}

void XL_FSM_HEADER_3(XL_Receiver_FSM *fsm){
  if(FSM_BYTE != stuffing_byte){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_ID);
  }
  else{
    FSM_RESET;
  }
}

void XL_FSM_ID(XL_Receiver_FSM *fsm){
  if(FSM_BYTE != 0xFF && FSM_BYTE != 0xFD){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_LENGTH_LOW);
  }
  else{
    FSM_RESET;
  }
}

void XL_FSM_LENGTH_LOW(XL_Receiver_FSM *fsm){
  fsm->remaining_bytes = FSM_BYTE;
  FSM_NEXT;
  FSM_UPDATE(XL_FSM_LENGTH_HIGH);
}

void XL_FSM_LENGTH_HIGH(XL_Receiver_FSM *fsm){
  fsm->remaining_bytes |= FSM_BYTE << 8;
  const uint16_t remaining_bytes = fsm->remaining_bytes;
  if((remaining_bytes >= 4) && (7 + remaining_bytes <= XL_BUFFER_SIZE)){
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_INSTRUCTION);
  }
  else{
    FSM_RESET;
  }
}
void XL_FSM_INSTRUCTION(XL_Receiver_FSM *fsm){
  if(FSM_BYTE == XL_STATUS){
    fsm->remaining_bytes--;
    FSM_NEXT;
    FSM_UPDATE(XL_FSM_RECEIVING);
  }else{
    FSM_RESET;
  }
}

void XL_FSM_RECEIVING(XL_Receiver_FSM *fsm){
  FSM_NEXT;
  fsm->remaining_bytes--;
  if(fsm->remaining_bytes == 0){
    fsm->done = 1;
  }
}

uint8_t XL_Extract_Status_Packet(XL_Status_Packet *packet, uint8_t frame[XL_BUFFER_SIZE], uint16_t length){
  //La taille est supposée vérifiée dans XL_Receive.
  //CRC
  uint16_t old_crc = (frame[length-1] << 8) | frame[length-2];
  uint16_t new_crc = XL_Update_CRC(0, frame, length-2);
  if(new_crc != old_crc){
    err = XL_ERR_LINK | XL_ERR_BAD_FRAME;
    return 1;
  }

  packet->id = frame[4];
  packet->err = frame[8];

  //Paramètres
  uint8_t *start_stuffing = frame+7;
  uint8_t *end_stuffing = frame+(length-2);
  uint8_t *p_frame = frame+9;

  packet->nb_params = 0;
  while(p_frame != end_stuffing){
    packet->params[packet->nb_params++] = *(p_frame++);
    if(p_frame - start_stuffing == 3){
      if(start_stuffing[0] == header[0] && start_stuffing[1] == header[1] && start_stuffing[2] == header[2]){
	if(*p_frame != stuffing_byte){
	  err = XL_ERR_LINK | XL_ERR_BAD_FRAME;
	  return 1;
	}
	p_frame++;
	start_stuffing = p_frame;
      }
      else{
	start_stuffing++;
      }
    }
  }
  
  return 0;
}

uint8_t XL_Receive(XL_Interface *interface, uint16_t packet_size, uint32_t timeout){
  //Evite un overflow
  if(packet_size > XL_BUFFER_SIZE){
    err = XL_ERR_INTERNAL | XL_ERR_BUFFER_OVERFLOW;
    return 1;
  }
  
  //Préparation de la réception
  interface->set_direction(XL_RECEIVE);
  
  interface->fsm.update_state = XL_FSM_HEADER_0;
  interface->fsm.remaining_bytes = 0;
  interface->fsm.buffer = interface->buffer;
  interface->fsm.p_buffer = interface->buffer;
  interface->fsm.done = 0;

  //Réception
  if(interface->receive(interface->fsm.p_buffer, packet_size, timeout) != 0){
    err = XL_ERR_LINK | XL_ERR_TIMEOUT;
    return 1;
  }

  //FSM
  do{
    interface->fsm.update_state(&(interface->fsm));

    /*uint8_t *p;
    printf("Buffer : ");
    for(p = interface->buffer; p < interface->fsm.p_buffer; p++){
      printf("0x%2.2X ", *p);
    }
    printf("\n");*/
  }while(interface->fsm.p_buffer != interface->fsm.buffer && interface->fsm.done != 1);

  //Récupération du paquet
  if(interface->fsm.done == 0){
    err = XL_ERR_LINK | XL_ERR_BAD_FRAME;
    return 1;
  }

  //Vérification de la taille du paquet (au cas où)
  uint16_t r_packet_size = interface->fsm.p_buffer - interface->fsm.buffer;
  if(r_packet_size != packet_size){
    err = XL_ERR_LINK | XL_ERR_BAD_FRAME;
    return 1;
  }

  return XL_Extract_Status_Packet(&interface->status, interface->buffer, packet_size);
}

//======================================
//           FONCTIONS D'ENVOI          
//======================================
uint8_t XL_Build_Frame(XL_Instruction_Packet *packet, uint8_t buffer[XL_BUFFER_SIZE]){
  //Vérification des arguments
  if(packet == 0 || (packet->params == 0 && packet->nb_params > 0) || buffer == 0){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 0;
  }
  //Evite une collision avec l'en-tête
  if(packet->id == 0xFD || packet->id == 0xFF){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 0;
  }
  //Evite un overflow
  if(10+packet->nb_params+packet->nb_params/3 > XL_BUFFER_SIZE){
    err = XL_ERR_INTERNAL | XL_ERR_BUFFER_OVERFLOW;
    return 0;
  }

  uint8_t *p_buffer = buffer;
  //Header
  *(p_buffer++) = header[0];
  *(p_buffer++) = header[1];
  *(p_buffer++) = header[2];
  *(p_buffer++) = header[3];

  //Packet ID
  *(p_buffer++) = packet->id;

  //Packet length (temporaire)
  p_buffer += 2;

  //<BEGIN BYTE STUFFING>
  //Instruction
  uint8_t *start_stuffing = p_buffer;
  *(p_buffer++) = packet->instruction;

  //Paramètres
  int i;
  for(i = 0; i < packet->nb_params; i++){
    *(p_buffer++) = packet->params[i];
    if(p_buffer - start_stuffing == 3){
      if(start_stuffing[0] == header[0] && start_stuffing[1] == header[1] && start_stuffing[2] == header[2]){
	*(p_buffer++) = stuffing_byte;
	start_stuffing = p_buffer;
      }else{
	start_stuffing++;
      }
    }
  }
  //<END BYTE STUFFING>

  //Packet length
  uint16_t packet_length = (p_buffer-buffer) - 7 + 2;//Ce qu'on a écrit - (header+id+length) + crc
  buffer[5] = packet_length & 0x00FF;
  buffer[6] = packet_length >> 8;

  //Cyclic Redundancy Check
  uint16_t crc = XL_Update_CRC(0, buffer, packet_length+7-2);
  *(p_buffer++) = crc & 0x00FF;
  *(p_buffer++) = crc >> 8;
  
  return p_buffer-buffer;    
}

uint8_t XL_Send(XL_Interface *interface, XL_Instruction_Packet *packet, uint32_t timeout){
  //Préparation de la trame
  uint8_t length = XL_Build_Frame(packet, interface->buffer);
  if(!length){
    return 1;
  }

  //Envoi
  interface->set_direction(XL_SEND);
  if(interface->send(interface->buffer, length, timeout) == 1){
    err = XL_ERR_LINK | XL_ERR_TIMEOUT;
    return 1;
  }
  return 0;
}

uint16_t XL_Update_CRC(uint16_t crc_accum, uint8_t *data_blk_ptr, uint16_t data_blk_size){
  uint16_t i, j;
  uint16_t crc_table[256] = {
    0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
    0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
    0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
    0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
    0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
    0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
    0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
    0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
    0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
    0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
    0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
    0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
    0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
    0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
    0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
    0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
    0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
    0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
    0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
    0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
    0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
    0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
    0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
    0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
    0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
    0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
    0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
    0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
    0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
    0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
    0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
    0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202};

  for(j = 0; j < data_blk_size; j++){
      i = ((uint16_t)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
      crc_accum = (crc_accum << 8) ^ crc_table[i];
  }

  return crc_accum;
}

//======================================
//         GESTION DES ERREURS      
//======================================
uint16_t XL_Get_Error(){
  return err;
}

uint8_t XL_Check_Status(XL *servo){
  if(XL_STATUS_ERROR(servo->interface->status.err) != 0){
    err = XL_ERR_STATUS | XL_STATUS_ERROR(servo->interface->status.err);
    return 1;
  }
  return 0;
}

uint8_t XL_Check_Alert(XL *servo){
  if(XL_STATUS_ALERT(servo->interface->status.err) == 1){
    uint16_t hw_error;
    if(XL_Get_Hardware_Error(servo, &hw_error) == 1){
      return 1;
    }
    err = XL_ERR_HARDWARE | hw_error;
    return 1;
  }
  return 0;
}


//======================================
//         JEU D'INSTRUCTIONS      
//======================================
uint8_t XL_Ping(XL *servo){
  if(servo == 0){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  
  XL_Instruction_Packet packet;
  packet.id = servo->id;
  packet.instruction = XL_PING;
  packet.nb_params = 0;
  packet.params = 0;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Réception de la réponse
  if(XL_Receive(servo->interface, 14, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Vérification de la réponse
  return XL_Check_Status(servo);
}

uint8_t XL_Discover(XL_Interface *interface, XL *buffer_servos, uint8_t len_buffer, uint16_t *nb_servos){
  XL servo;
  servo.interface = interface;

  *nb_servos = 0;
  for(servo.id = 0x00; servo.id < 0xFD && (*nb_servos < len_buffer); servo.id++){
    if(XL_Ping(&servo) == 0){
      buffer_servos[(*nb_servos)++] = servo;
    }
  }
  
  return (*nb_servos > 0)?0:1;
}

uint8_t XL_Say_Hello(XL *servo){
  if(XL_Ping(servo) == 1){
    return 1;
  }

  const XL_LED_Color color = (servo->interface->status.err == 0x00)?XL_GREEN:XL_RED;
  uint8_t i;
  for(i = 0; i < servo->id; i++){
    XL_Set_LED(servo, color, XL_NOW);
    servo->interface->delay(500);
    XL_Set_LED(servo, XL_LED_OFF, XL_NOW);
    servo->interface->delay(500);
  }

  return 0;
}

uint8_t XL_Read(XL *servo, XL_Field field, uint16_t *data){
  if(field > XL_NB_FIELDS-1){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  
  //Préparation de l'instruction READ
  XL_Instruction_Packet packet;
  packet.id = servo->id;
  packet.instruction = XL_READ;
  packet.nb_params = 4;
  uint8_t params[4] = {field_addr[field], 0x00, field_length[field], 0x00};
  packet.params = params;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }
  
  //Réception de la réponse
  if(XL_Receive(servo->interface, 11+field_length[field], XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Vérification de la réponse
  if(XL_Check_Status(servo) == 1){
    return 1;
  }
  
  //Récupération de la donnée
  *data = servo->interface->status.params[0];
  if(field_length[field] == 2){
    *data |= servo->interface->status.params[1] << 8;
  }
  return 0;
}

uint8_t XL_Action(XL *servo){
  //Préparation de l'instruction
  XL_Instruction_Packet packet;
  packet.id = servo->id;
  packet.instruction = XL_ACTION;
  packet.nb_params = 0;
  packet.params = 0;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Réception de la réponse
  if(XL_Receive(servo->interface, 11, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //En cas d'erreur matérielle
  if(XL_Check_Alert(servo) == 1){
    return 1;
  }

  //Vérification du status
  if(XL_Check_Status(servo) == 1){
    return 1;
  }

  //Action OK
  return 0;
}

uint8_t XL_Factory_Reset(XL *servo){
  XL_Instruction_Packet packet;
  packet.id = servo->id;
  packet.instruction = XL_FACTORY_RESET;
  packet.nb_params = 1;
  uint8_t param = 0x02;
  packet.params = &param;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Attente de la réinitialisation
  servo->interface->delay(5000);
  
  return 0;
}

uint8_t XL_Reboot(XL *servo){
  XL_Instruction_Packet packet;
  packet.id = servo->id;
  packet.instruction = XL_REBOOT;
  packet.nb_params = 0;
  packet.params = 0;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Attente du redémarrage
  servo->interface->delay(5000);
  
  return 0;
}

uint8_t XL_Write(XL *servo, XL_Field field, uint16_t data, uint8_t size, uint8_t now){
  if(servo == 0 || field > (XL_NB_FIELDS-1)){
    return 1;
  }

  //Préparation de l'instruction
  static XL_Instruction_Packet packet;
  static uint8_t params[4];
  params[0] = field_addr[field];
  params[1] = 0x00;
  params[2] = data & 0xFF;
  params[3] = data >> 8;
  packet.id = servo->id;
  packet.instruction = now?XL_WRITE:XL_REG_WRITE;
  packet.nb_params = 2 + size;
  packet.params = params;

  //Envoi de l'instruction
  if(XL_Send(servo->interface, &packet, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //Réception de la réponse
  if(XL_Receive(servo->interface, 11, XL_DEFAULT_TIMEOUT) == 1){
    return 1;
  }

  //En cas d'erreur matérielle
  if(XL_Check_Alert(servo) == 1){
    return 1;
  }

  //Vérification du status
  if(XL_Check_Status(servo) == 1){
    return 1;
  }

  //Write OK
  return 0;
}

//======================================
//         CONFIGURATION EEPROM       
//======================================
uint8_t XL_Configure_ID(XL *servo, uint8_t id){
  if(id > 252){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_ID, id, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Baud_Rate(XL *servo, XL_Baud_Rate baud_rate){
  if(baud_rate != XL_BAUD_RATE_9600 && baud_rate != XL_BAUD_RATE_57600 && baud_rate != XL_BAUD_RATE_115200 && baud_rate != XL_BAUD_RATE_1MBPS){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_BAUD_RATE, baud_rate, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Return_Delay_Time(XL *servo, uint8_t delay){
  if(delay > 0xFE){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_RETURN_DELAY_TIME, delay, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_CW_Angle_Limit(XL *servo, uint16_t angle){
  if(angle > 0x3FF){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_CW_ANGLE_LIMIT, angle, 2, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_CCW_Angle_Limit(XL *servo, uint16_t angle){
  if(angle > 0x3FF){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_CCW_ANGLE_LIMIT, angle, 2, XL_NOW);
  servo->interface->delay(10);
  return r;
}
  
uint8_t XL_Configure_Control_Mode(XL *servo, XL_Mode mode){
  if(mode != XL_JOIN_MODE && mode != XL_WHEEL_MODE){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_CONTROL_MODE, mode, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Limit_Temperature(XL *servo, uint8_t temp){
  if(temp > 150){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_LIMIT_TEMPERATURE, temp, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Lower_Limit_Voltage(XL *servo, uint8_t voltage){
  if(voltage < 50 || voltage > 250){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_LOWER_LIMIT_VOLTAGE, voltage, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Upper_Limit_Voltage(XL *servo, uint8_t voltage){
  if(voltage < 50 || voltage > 250){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_UPPER_LIMIT_VOLTAGE, voltage, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Max_Torque(XL *servo, uint16_t max_torque){
  if(max_torque > 1023){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_MAX_TORQUE, max_torque, 2, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Return_Level(XL *servo, XL_Return_Level level){
  if(level != XL_PING_RETURN && level != XL_READ_RETURN && level != XL_ALL_RETURN){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_RETURN_LEVEL, level, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}

uint8_t XL_Configure_Alarm_Shutdown(XL *servo, XL_Alarm_Shutdown alarm){
  if(alarm > XL_ERROR_OVER_9000){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  uint8_t r = XL_Write(servo, XL_ALARM_SHUTDOWN, alarm, 1, XL_NOW);
  servo->interface->delay(10);
  return r;
}


//======================================
//       COMMANDES SERVOMOTEUR       
//======================================

uint8_t XL_Power_On(XL *servo, uint8_t now){
  return XL_Write(servo, XL_TORQUE_ENABLE, 1, 1, now);
}

uint8_t XL_Power_Off(XL *servo, uint8_t now){
  return XL_Write(servo, XL_TORQUE_ENABLE, 0, 1, now);
}

uint8_t XL_Set_LED(XL *servo, XL_LED_Color color, uint8_t now){
  if((uint8_t) color > 7){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_LED, color, 1, now);
}

uint8_t XL_Set_D_Gain(XL *servo, uint8_t d_gain, uint8_t now){
  if(d_gain > 254){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_D_GAIN, d_gain, 1, now);
}

uint8_t XL_Set_I_Gain(XL *servo, uint8_t i_gain, uint8_t now){
  if(i_gain > 254){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_I_GAIN, i_gain, 1, now);
}

uint8_t XL_Set_P_Gain(XL *servo, uint8_t p_gain, uint8_t now){
  if(p_gain > 254){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_P_GAIN, p_gain, 1, now);
}

uint8_t XL_Set_Goal_Position(XL *servo, uint16_t position, uint8_t now){
  if(position > 1023){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_GOAL_POSITION, position, 2, now);
}

uint8_t XL_Set_Goal_Speed_Join(XL *servo, uint16_t speed, uint8_t now){
  if(speed > 1023){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_MOVING_SPEED, speed, 2, now); 
}

uint8_t XL_Set_Goal_Speed_Wheel(XL *servo, uint16_t speed, XL_Wheel_Direction dir, uint8_t now){
  if(speed > 1023){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  switch(dir){
  case XL_CLOCKWISE:
    speed += 1024;
    break;
  case XL_COUNTERCLOCKWISE:
  break;
  default:
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
    break;
  }
  return XL_Write(servo, XL_MOVING_SPEED, speed, 2, now);
}

uint8_t XL_Set_Torque_Limit(XL *servo, uint16_t torque_limit, uint8_t now){
  if(torque_limit > 1023){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_TORQUE_LIMIT, torque_limit, 2, now);
}

uint8_t XL_Set_Punch(XL *servo, uint16_t punch, uint8_t now){
  if(punch < 0x20 || punch > 0x3FF){
    err = XL_ERR_INTERNAL | XL_ERR_ILLEGAL_ARGUMENTS;
    return 1;
  }
  return XL_Write(servo, XL_PUNCH, punch, 2, now);
}

//======================================
//       LECTURE D'INFORMATIONS
//======================================
uint8_t XL_Get_Current_Position(XL *servo, uint16_t *position){
  return XL_Read(servo, XL_CURRENT_POSITION, position);
}

uint8_t XL_Get_Current_Speed(XL *servo, XL_Wheel_Direction *direction, uint16_t *speed){
  if(XL_Read(servo, XL_CURRENT_SPEED, speed) == 1){
    return 1;
  }
  *direction = (*speed > 1023)?XL_CLOCKWISE:XL_COUNTERCLOCKWISE;
  *speed &= 0x3FF;
  return 0;
}

uint8_t XL_Get_Current_Load(XL *servo, XL_Wheel_Direction *direction, uint16_t *load){
  if(XL_Read(servo, XL_CURRENT_LOAD, load) == 1){
    return 1;
  }
  *direction = (*load > 1023)?XL_CLOCKWISE:XL_COUNTERCLOCKWISE;
  *load &= 0x3FF;
  return 0;
}

uint8_t XL_Get_Current_Voltage(XL *servo, uint16_t *voltage){
  return XL_Read(servo, XL_CURRENT_VOLTAGE, voltage);
}

uint8_t XL_Get_Current_Temperature(XL *servo, uint16_t *temperature){
  return XL_Read(servo, XL_CURRENT_TEMPERATURE, temperature);
}

uint8_t XL_Is_Working(XL *servo, uint16_t *working){
  return XL_Read(servo, XL_TORQUE_ENABLE, working);
}

uint8_t XL_Is_Moving(XL *servo, uint16_t *moving){
  return XL_Read(servo, XL_MOVING, moving);
}

uint8_t XL_Get_Hardware_Error(XL *servo, uint16_t *hw_error){
  return XL_Read(servo, XL_HARDWARE_ERROR_STATUS, hw_error);
}
