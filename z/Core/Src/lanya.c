#include "lanya.h"
#include "my_printf.h"


uint8_t Rx_len ;   //�ܹ����յĳ���
uint8_t RX_flag ;  //������ɵı�׼
uint8_t RxBuffer[RXBUFFER_LEN];  //���մ洢



void Check_Rx()
{
		if(RX_flag == 1)   //�ж��Ƿ�������
		{
				uart3_printf("I got the message %s",RxBuffer);
				for(uint8_t i=0;i<20;i++)  //������յı�־
				{
						RxBuffer[i] = 0;
				}
				Rx_len=0;
				RX_flag = 0;
		}
}

