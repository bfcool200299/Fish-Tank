#include "uart_task.h"
#include "sg90.h"
#include "ws2812b.h"
//串口功能 接受串口信息处理

uint8_t usart_screen;  //读取串口接受值
uint8_t RGBLcok;
uint8_t DuoJiLock;    //舵机开关锁
uint8_t RGBStaus;
//处理浮点数保留两位
uint32_t Decimal_2(float DataP)
{
	uint32_t DataF;
	DataF = (uint32_t)(100 * DataP + 0.5) ;
	return DataF;
}
//处理浮点数保留一位
uint32_t Decimal_1(float DataP)
{
	uint32_t DataF;
	DataF = (uint32_t)(10 * DataP + 0.5) ;
	return DataF;
}

//屏幕温度浮点数输出函数
void HMI_Printf_F_WenDu(uint32_t val,uint32_t vvs)
{
		printf("main.x0.val=%d",val); //发送数值
    printf("\xff\xff\xff"); //发送结束符
		printf("main.x0.vvs1=%d",vvs); //发送命令
    printf("\xff\xff\xff"); //发送结束符
}
//屏幕光照浮点数输出函数
void HMI_Printf_F_GuangZhao(uint32_t val,uint32_t vvs)
{
		printf("main.x2.val=%d",val); //发送数值
    printf("\xff\xff\xff"); //发送结束符
		printf("main.x2.vvs1=%d",vvs); //发送命令
    printf("\xff\xff\xff"); //发送结束符
}
//屏幕TDS输出函数
void HMI_Printf_F_TDS(uint32_t val,uint32_t vvs)
{
		printf("main.x3.val=%d",val); //发送数值
    printf("\xff\xff\xff"); //发送结束符
		printf("main.x3.vvs1=%d",vvs); //发送命令
    printf("\xff\xff\xff"); //发送结束符
}
//屏幕浑浊度输出函数
void HMI_Printf_F_HunZhuo(uint32_t val,uint32_t vvs)
{
		printf("main.x1.val=%d",val); //发送数值
    printf("\xff\xff\xff"); //发送结束符
		printf("main.x1.vvs1=%d",vvs); //发送命令
    printf("\xff\xff\xff"); //发送结束符
}
//串口中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	//串口屏usart1
	if(huart->Instance==USART1)
	{
		
		switch(usart_screen)
		{
			case ZhiYangOpen:
				HAL_GPIO_WritePin(GPIOA,MadeO2_Pin,GPIO_PIN_SET);
			break;
			
			case ZhiYangOff:
				HAL_GPIO_WritePin(GPIOA,MadeO2_Pin,GPIO_PIN_RESET);
			break;
			
			case ShuiOpen:
				HAL_GPIO_WritePin(GPIOA,GuoLv_Pin,GPIO_PIN_SET);
			break;
			
			case ShuiOff:
				HAL_GPIO_WritePin(GPIOA,GuoLv_Pin,GPIO_PIN_RESET);
			break;
			
			case DengGuangOn:
				HAL_GPIO_WritePin(GPIOA,LED_Pin,GPIO_PIN_SET);
			break;
			
			case DengGuangOff:
					HAL_GPIO_WritePin(GPIOA,LED_Pin,GPIO_PIN_RESET);
			break;
			
			case JiaReOpen:
						HAL_GPIO_WritePin(GPIOB,JiaRe_Pin,GPIO_PIN_SET);
			break;
			
			case JiaReOff:
						HAL_GPIO_WritePin(GPIOB,JiaRe_Pin,GPIO_PIN_RESET);
			break;
				
			case RGBOn :
				RGBLcok = 1;
				break;
			case RGBOff:
				RGBLcok = 0;
			break;
			
			case Raninbow:
				RGBStaus = 1;
				break;
				
				case Sea:
				RGBStaus = 2;
				break;
				
				case Sengling:
				RGBStaus = 3;
				break;
				
				case HuangMo:
				RGBStaus = 4;
				break;
				
				case ChouShuiOn:
					HAL_GPIO_WritePin(GPIOB,Choushui_Pin,GPIO_PIN_SET);
					break;
				
				case ChouShuiOff:
					HAL_GPIO_WritePin(GPIOB,Choushui_Pin,GPIO_PIN_RESET);
					break;
				
				case FeedOne:
					DuojiLock = 1;
					Duoji_Mode = 1;
					break;
				
				case FeedTwo:
					DuojiLock = 1;
					Duoji_Mode = 2;
					break;
				
				case FeedThree:
					DuojiLock =1;
				  Duoji_Mode = 3;
					break;
				
				case FeedFour:
					DuojiLock =1;
				  Duoji_Mode = 4;
					break;
				
				case FeedFive:
					DuojiLock =1;
				  Duoji_Mode = 5;
					break;
				
				case FeedSix:
					DuojiLock =1;
				  Duoji_Mode = 6;
					break;
			default:
			 break;
		}
		//HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);   //串口屏
		//防止多次RECeive接收不到，出现错误
	
		}
	
		HAL_StatusTypeDef ret_state = HAL_UART_Receive_IT(&huart1, &usart_screen, 1);
		if (ret_state == HAL_BUSY) {
	 
				__HAL_UART_CLEAR_OREFLAG(&huart1);  // 由于ORE寄存器导致的出错
			huart1.RxState = HAL_UART_STATE_READY;
			huart1.Lock = HAL_UNLOCKED;
			HAL_UART_Receive_IT(&huart1, &usart_screen, 1);
		}	
}
	
		



