#ifndef LAN_YA_H
#define LAN_YA_H

#include "usart.h"
#include "stdio.h"

#define RXBUFFER_LEN 20

void Check_Rx(void); 
extern uint8_t Rx_len ;   //�ܹ����յĳ���
extern uint8_t RX_flag ;  //������ɵı�׼
extern uint8_t RxBuffer[RXBUFFER_LEN]; 

#endif

