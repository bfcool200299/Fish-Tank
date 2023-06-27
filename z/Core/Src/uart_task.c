#include "uart_task.h"
#include "sg90.h"
#include "ws2812b.h"
//���ڹ��� ���ܴ�����Ϣ����

uint8_t usart_screen;  //��ȡ���ڽ���ֵ
uint8_t RGBLcok;
uint8_t DuoJiLock;    //���������
uint8_t RGBStaus;
//��������������λ
uint32_t Decimal_2(float DataP)
{
	uint32_t DataF;
	DataF = (uint32_t)(100 * DataP + 0.5) ;
	return DataF;
}
//������������һλ
uint32_t Decimal_1(float DataP)
{
	uint32_t DataF;
	DataF = (uint32_t)(10 * DataP + 0.5) ;
	return DataF;
}

//��Ļ�¶ȸ������������
void HMI_Printf_F_WenDu(uint32_t val,uint32_t vvs)
{
		printf("main.x0.val=%d",val); //������ֵ
    printf("\xff\xff\xff"); //���ͽ�����
		printf("main.x0.vvs1=%d",vvs); //��������
    printf("\xff\xff\xff"); //���ͽ�����
}
//��Ļ���ո������������
void HMI_Printf_F_GuangZhao(uint32_t val,uint32_t vvs)
{
		printf("main.x2.val=%d",val); //������ֵ
    printf("\xff\xff\xff"); //���ͽ�����
		printf("main.x2.vvs1=%d",vvs); //��������
    printf("\xff\xff\xff"); //���ͽ�����
}
//��ĻTDS�������
void HMI_Printf_F_TDS(uint32_t val,uint32_t vvs)
{
		printf("main.x3.val=%d",val); //������ֵ
    printf("\xff\xff\xff"); //���ͽ�����
		printf("main.x3.vvs1=%d",vvs); //��������
    printf("\xff\xff\xff"); //���ͽ�����
}
//��Ļ���Ƕ��������
void HMI_Printf_F_HunZhuo(uint32_t val,uint32_t vvs)
{
		printf("main.x1.val=%d",val); //������ֵ
    printf("\xff\xff\xff"); //���ͽ�����
		printf("main.x1.vvs1=%d",vvs); //��������
    printf("\xff\xff\xff"); //���ͽ�����
}
//�����ж�
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	//������usart1
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
		//HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);   //������
		//��ֹ���RECeive���ղ��������ִ���
	
		}
	
		HAL_StatusTypeDef ret_state = HAL_UART_Receive_IT(&huart1, &usart_screen, 1);
		if (ret_state == HAL_BUSY) {
	 
				__HAL_UART_CLEAR_OREFLAG(&huart1);  // ����ORE�Ĵ������µĳ���
			huart1.RxState = HAL_UART_STATE_READY;
			huart1.Lock = HAL_UNLOCKED;
			HAL_UART_Receive_IT(&huart1, &usart_screen, 1);
		}	
}
	
		



