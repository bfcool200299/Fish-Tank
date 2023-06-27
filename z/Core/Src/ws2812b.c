#include "ws2812b.h"
#include "tim.h"
//PA 12
//RGB1sFlag 标志位

uint16_t  RGB_buffur[RESET_PULSE + WS2812_DATA_LEN] = { 0 };
//关闭rgb
void OFFRGB(void)
{
	for(uint8_t i = 0; i < 30; i++)
			{
				ws2812_set_RGB(0, 0, 0, i);
			}
			
			HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + 30 * 24));
}
//模式1 海洋之旅
void ModeFirst(void)
{
	static uint8_t R,G,B;
	static uint8_t temp;

	(temp<5)?(temp++):(temp = 0);
	 
	if(RGB1sFlag == 1)
	{
			
			switch(temp)
			{
				case 0:
					R = 0;G = 0;B = 255;
					break;
				
				case 1:
					R = 0;G = 102;B = 204;
					break;
				
				case 2:
					R = 0;G = 68;B = 170;
					break;
				
				case 3:
					R = 0;G = 56;B = 180;
					break;	
				
		    case 4:
					R = 0;G = 47;B = 200;
					break;
			}
			
			for(uint8_t i = 0; i < 30; i++)
			{
				ws2812_set_RGB(R, G, B, i);
			}
			
			HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + 30 * 24));
			
			RGB1sFlag = 0;
	}
}
//模式2  绿色之旅
void ModeSecond(void)
{
	static uint8_t R,G,B;
	static uint8_t temp;

	(temp<5)?(temp++):(temp = 0);
	 
	if(RGB1sFlag == 1)
	{
			switch(temp)
			{
	 			case 0:
					R = 54;G = 189;B = 54;
					break;
				
				case 1:
					R = 30;G = 179;B = 43;
					break;
				
				case 2:
					R = 46;G = 219;B = 60;
					break;
				
				case 3:
					R =20;G = 170;B = 20;
					break;
				
					case 4:
					R = 30;G = 220;B = 40;
					break;	
			}
			
			for(uint8_t i = 0; i < 30; i++)
			{
				ws2812_set_RGB(R, G, B, i);
			}
			
			HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + 30 * 24));
			RGB1sFlag = 0;
	}
}
//模式3  荒漠之旅
void ModeThird(void)
{
	static uint8_t R,G,B;
	static uint8_t temp;

	(temp<5)?(temp++):(temp = 0);
	 
	if(RGB1sFlag == 1)
	{						
			switch(temp)
			{
				case 0:
					R = 240;G = 230;B = 48;
					break;
				
				case 1:
					R = 218;G = 165;B = 32;
					break;
				
				case 2:
					R = 200;G = 183;B = 50;
					break;
				
				case 3:
					R = 205;G = 133;B = 40;
					break;	
				
					case 4:
					R = 240;G = 200;B = 30;
					break;	
			}
			
			for(uint8_t i = 0; i < 30; i++)
			{
				ws2812_set_RGB(R, G, B, i);
			}
			
			HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + 30 * 24));
			RGB1sFlag = 0;
	}
}
//彩虹灯
void Mode_RaninBow(void)
{
	static uint8_t i;
	
	 if(RGB20msFlag == 1)
	 {
		 if(i<30)
		 {
				switch ( i % 7)
				{
					case 0:
						ws2812_set_RGB(0, 100, 100, i);
						break;
					
					case 1:
						ws2812_set_RGB(0, 35, 100, i);
						break;
					
					case 2:
						ws2812_set_RGB(0, 0, 100, i);
						break;
					
					case 3:
						ws2812_set_RGB(100, 0, 100, i);
						break;
					
					case 4:
						ws2812_set_RGB(100, 50, 0, i);
						break;
					
					case 5:
						ws2812_set_RGB(100, 100, 0, i);
						break;
					
					case 6:
						ws2812_set_RGB(15, 100, 0, i);
						break;
				}
				
				i++;
				HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + i * 24));
			}
		 else if(i<60)
		 {
			 ws2812_set_RGB(0,0,0,i-30);
			 i++;
			 HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(80 + 30* 24));
			 
		 }else if(i >= 60)
		 {
			 i = 0;
		 }
			
			
		  RGB20msFlag = 0;
		}
}
void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num)
{
    //
    uint16_t* p = (RGB_buffur + RESET_PULSE) + (num * LED_DATA_LEN);
    
    for (uint16_t i = 0;i < 8;i++)
    {
        //
        p[i]      = (G << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 8]  = (R << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 16] = (B << i) & (0x80)?ONE_PULSE:ZERO_PULSE;

    }
}
/*ws2812 初始化*/
void ws2812_init(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(num_data)); 
}

/*全亮蓝灯*/
void ws2812_blue(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0x22, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(num_data));
}
/*全亮红灯*/
void ws2812_red(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x22, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(num_data));
}
/*全亮绿灯*/
void ws2812_green(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x22, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(num_data));
}

//void ws2812_example(void)
//{		
//	  ws2812_set_RGB(0x00, 0x00, 0x22, 0);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 1);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 2);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 3);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 6);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 7);
//		ws2812_set_RGB(0x00, 0x00, 0x22, 8);
//    ws2812_set_RGB(0x00, 0x00, 0x22, 10);
//    HAL_TIM_PWM_Start_DMA(&htim4,TIM_CHANNEL_2,(uint32_t *)RGB_buffur,(344)); //344 = 80 + 24 * LED_NUMS(11)

//    HAL_Delay(500);
//}

