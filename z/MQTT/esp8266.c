
#include "MQTT_Conf.h"
#include "uart_task.h"
#include "sg90.h"

uint8_t usart_screen;  //��ȡ���ڽ���ֵ
uint8_t DuoJiLock;    //���������

unsigned char esp8266_buf[128];
unsigned char a_esp8266_buf;
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;


//==========================================================
//	�������ƣ�	ESP8266_Clear
//
//	�������ܣ�	��ջ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	�������ƣ�	ESP8266_WaitRecive
//
//	�������ܣ�	�ȴ��������
//
//	��ڲ�����	��
//
//	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
//
//	˵����		ѭ�����ü���Ƿ�������
//==========================================================
_Bool ESP8266_WaitRecive(void)
{
	


	if(esp8266_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
	{
		return REV_WAIT;
	}
	if(esp8266_cnt == esp8266_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		esp8266_cnt = 0;							//��0���ռ���
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	esp8266_cntPre = esp8266_cnt;					//��Ϊ��ͬ
	{
	return REV_WAIT;								//���ؽ���δ��ɱ�־
	}

}

//==========================================================
//	�������ƣ�	ESP8266_SendCmd
//
//	�������ܣ�	��������
//
//	��ڲ�����	cmd������
//				res����Ҫ���ķ���ָ��
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{

	unsigned char timeOut = 200;
	HAL_UART_Transmit(&ESP_UART, (unsigned char *)cmd, strlen((const char *)cmd),0xffff);
    
	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//����յ�����
		{
			USER_PRINTF("%s",esp8266_buf);
			
			if(strstr((const char *)esp8266_buf, res) != NULL)		//����������ؼ���
			{
				
				ESP8266_Clear();									//��ջ���
				
				return 0;
			}
		}
		
		Delay_Us(10000);
	}

	return 1;

}

//==========================================================
//	�������ƣ�	ESP8266_SendData
//
//	�������ܣ�	��������
//
//	��ڲ�����	data������
//				len������
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_SendData(unsigned char *data, unsigned short len)
{

	char cmdBuf[32];
	
	ESP8266_Clear();								//��ս��ջ���
	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//��������
	if(!ESP8266_SendCmd(cmdBuf, ">"))				//�յ���>��ʱ���Է�������
	{
		HAL_UART_Transmit(&ESP_UART, data, len,0xffff);		//�����豸������������
	}

}

//==========================================================
//	�������ƣ�	ESP8266_GetIPD
//
//	�������ܣ�	��ȡƽ̨���ص�����
//
//	��ڲ�����	�ȴ���ʱ��(����10ms)
//
//	���ز�����	ƽ̨���ص�ԭʼ����
//
//	˵����		��ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
//				��ESP8266�ķ��ظ�ʽΪ	"+IPD,x:yyy"	x�������ݳ��ȣ�yyy����������
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//����������
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//������IPD��ͷ
			if(ptrIPD == NULL)											//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
			{
				//UsartUSER_PRINTF(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		Delay_Us(5000);												//��ʱ�ȴ�
	} while(timeOut--);
	
	return NULL;														//��ʱ��δ�ҵ������ؿ�ָ��

}

//==========================================================
//	�������ƣ�	ESP8266_Init
//
//	�������ܣ�	��ʼ��ESP8266
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_Init(void)
{
    
    
	//��esp8266�Ƚ��и�λ
    HAL_GPIO_WritePin(ESP8266_REST_GPIO_Port,ESP8266_REST_Pin,GPIO_PIN_RESET);
    HAL_Delay(250);
    HAL_GPIO_WritePin(ESP8266_REST_GPIO_Port,ESP8266_REST_Pin,GPIO_PIN_SET);
    HAL_Delay(500);
    
	ESP8266_Clear();
	
	USER_PRINTF("0. AT\r\n");
	while(ESP8266_SendCmd("AT\r\n", "OK"))
		HAL_Delay(500);
    
    USER_PRINTF( "1. RST\r\n");
	ESP8266_SendCmd("AT+RST\r\n", "");
	    HAL_Delay(500);
	
	USER_PRINTF("2. CWMODE\r\n");
	while(ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK"))
		HAL_Delay(500);
	
	USER_PRINTF("3. AT+CWDHCP\r\n");
	while(ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK"))
		HAL_Delay(500);
	
	USER_PRINTF("4. CWJAP\r\n");
	while(ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP"))
		HAL_Delay(500);
	
	USER_PRINTF("5. CIPSTART\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
		HAL_Delay(500);
	
	USER_PRINTF("6. ESP8266 Init OK\r\n");

}

//==========================================================
//	�������ƣ�	HAL_UART_RxCpltCallback
//
//	�������ܣ�	����2�շ��жϻص�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
	
	//������usart1
	if(huart->Instance==USART1)
	{

		switch(usart_screen)
		{
			case open:
			DuoJiLock = 1;
			uartx_printf("lock:%d\r\n",DuoJiLock);
			SG90_Rotate(Degrees_45);
			break;
			
			case off:
			SG90_Rotate(Degrees_0);
			DuoJiLock = 0;
			uartx_printf("lock:%d\r\n",DuoJiLock);
			break;
			
			case small:
			if(DuoJiLock ==1)
			{
				SG90_Rotate(Degrees_90);
			}
			break;
			
			case zhong:
			if(DuoJiLock ==1)
			{
				SG90_Rotate(Degrees_135);
			}
			break;
			case big:
				if(DuoJiLock ==1)
			{
				SG90_Rotate(Degrees_180);
			}
			break;
			default:
			 break;
		}
		//HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);   //������
		HAL_StatusTypeDef ret_state = HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);
		if (ret_state == HAL_BUSY) {
	 
				__HAL_UART_CLEAR_OREFLAG(&huart1);  // ����ORE�Ĵ������µĳ���
			huart1.RxState = HAL_UART_STATE_READY;
			huart1.Lock = HAL_UNLOCKED;
			HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);
		}
	}else if(huart->Instance==USART3)
	{
		if(esp8266_cnt >= 255)  //����ж�
	{
			esp8266_cnt = 0;
			memset(esp8266_buf,0x00,sizeof(esp8266_buf));
			HAL_UART_Transmit(&ESP_UART, (uint8_t *)"�������", 10,0xFFFF); 	
		}
		else
		{
			esp8266_buf[esp8266_cnt++] = a_esp8266_buf;   //��������ת��
		}
			HAL_UART_Receive_IT(&ESP_UART, (uint8_t *)&a_esp8266_buf, 1);   //�ٿ��������ж�
	}
	
	//��ֹ���RECeive���ղ��������ִ���

}
