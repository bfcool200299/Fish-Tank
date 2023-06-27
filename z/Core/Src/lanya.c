#include "lanya.h"
#include "my_printf.h"


uint8_t Rx_len ;   //总共接收的长度
uint8_t RX_flag ;  //接收完成的标准
uint8_t RxBuffer[RXBUFFER_LEN];  //接收存储



void Check_Rx()
{
		if(RX_flag == 1)   //判断是否接收完成
		{
				uart3_printf("I got the message %s",RxBuffer);
				for(uint8_t i=0;i<20;i++)  //清除接收的标志
				{
						RxBuffer[i] = 0;
				}
				Rx_len=0;
				RX_flag = 0;
		}
}

