#include "sg90.h"

uint8_t DuojiLock;
uint8_t Duoji_Mode;
//定时器3 PA6
void SG90_Rotate(uint16_t Degrees)
{

			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,Degrees); //一个周期内（20ms）有0.5ms高电平
			
}
void SG90_Mode(uint16_t Sudu)
{
	 if(DuojiLock == 1)
	 {
		 SG90_Rotate(Sudu);
	 }
	 
	 switch (Duoji_Mode)
	 {
		 case 1:
			 if(D_Mode_1 == 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_1 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
		 case 2:
			 if(D_Mode_2== 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_2 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
		 case 3:
			 if(D_Mode_3 == 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_3 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
		 case 4:
			 if(D_Mode_4 == 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_4 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
			 case 5:
			 if(D_Mode_5 == 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_5 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
			 case 6:
			 if(D_Mode_6 == 1)
			 {
				 Duoji_Mode = 0;
				 D_Mode_6 = 0;
				 SG90_Rotate(150);
				 DuojiLock = 0;
			 }
			 break;
			 
		 default:
			 SG90_Rotate(150);
			 break;
	}
	 
}




