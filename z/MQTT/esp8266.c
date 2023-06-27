
#include "MQTT_Conf.h"
#include "uart_task.h"
#include "sg90.h"

uint8_t usart_screen;  //读取串口接受值
uint8_t DuoJiLock;    //舵机开关锁

unsigned char esp8266_buf[128];
unsigned char a_esp8266_buf;
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;


//==========================================================
//	函数名称：	ESP8266_Clear
//
//	函数功能：	清空缓存
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	函数名称：	ESP8266_WaitRecive
//
//	函数功能：	等待接收完成
//
//	入口参数：	无
//
//	返回参数：	REV_OK-接收完成		REV_WAIT-接收超时未完成
//
//	说明：		循环调用检测是否接收完成
//==========================================================
_Bool ESP8266_WaitRecive(void)
{
	


	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
	{
		return REV_WAIT;
	}
	if(esp8266_cnt == esp8266_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		esp8266_cnt = 0;							//清0接收计数
		return REV_OK;								//返回接收完成标志
	}
		
	esp8266_cntPre = esp8266_cnt;					//置为相同
	{
	return REV_WAIT;								//返回接收未完成标志
	}

}

//==========================================================
//	函数名称：	ESP8266_SendCmd
//
//	函数功能：	发送命令
//
//	入口参数：	cmd：命令
//				res：需要检查的返回指令
//
//	返回参数：	0-成功	1-失败
//
//	说明：		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{

	unsigned char timeOut = 200;
	HAL_UART_Transmit(&ESP_UART, (unsigned char *)cmd, strlen((const char *)cmd),0xffff);
    
	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//如果收到数据
		{
			USER_PRINTF("%s",esp8266_buf);
			
			if(strstr((const char *)esp8266_buf, res) != NULL)		//如果检索到关键词
			{
				
				ESP8266_Clear();									//清空缓存
				
				return 0;
			}
		}
		
		Delay_Us(10000);
	}

	return 1;

}

//==========================================================
//	函数名称：	ESP8266_SendData
//
//	函数功能：	发送数据
//
//	入口参数：	data：数据
//				len：长度
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_SendData(unsigned char *data, unsigned short len)
{

	char cmdBuf[32];
	
	ESP8266_Clear();								//清空接收缓存
	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//发送命令
	if(!ESP8266_SendCmd(cmdBuf, ">"))				//收到‘>’时可以发送数据
	{
		HAL_UART_Transmit(&ESP_UART, data, len,0xffff);		//发送设备连接请求数据
	}

}

//==========================================================
//	函数名称：	ESP8266_GetIPD
//
//	函数功能：	获取平台返回的数据
//
//	入口参数：	等待的时间(乘以10ms)
//
//	返回参数：	平台返回的原始数据
//
//	说明：		不同网络设备返回的格式不同，需要去调试
//				如ESP8266的返回格式为	"+IPD,x:yyy"	x代表数据长度，yyy是数据内容
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//如果接收完成
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//搜索“IPD”头
			if(ptrIPD == NULL)											//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
			{
				//UsartUSER_PRINTF(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//找到':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		Delay_Us(5000);												//延时等待
	} while(timeOut--);
	
	return NULL;														//超时还未找到，返回空指针

}

//==========================================================
//	函数名称：	ESP8266_Init
//
//	函数功能：	初始化ESP8266
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Init(void)
{
    
    
	//将esp8266先进行复位
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
//	函数名称：	HAL_UART_RxCpltCallback
//
//	函数功能：	串口2收发中断回调函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
	
	//串口屏usart1
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
		//HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);   //串口屏
		HAL_StatusTypeDef ret_state = HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);
		if (ret_state == HAL_BUSY) {
	 
				__HAL_UART_CLEAR_OREFLAG(&huart1);  // 由于ORE寄存器导致的出错
			huart1.RxState = HAL_UART_STATE_READY;
			huart1.Lock = HAL_UNLOCKED;
			HAL_UART_Receive_IT(&huart1, (uint8_t *)&usart_screen, 1);
		}
	}else if(huart->Instance==USART3)
	{
		if(esp8266_cnt >= 255)  //溢出判断
	{
			esp8266_cnt = 0;
			memset(esp8266_buf,0x00,sizeof(esp8266_buf));
			HAL_UART_Transmit(&ESP_UART, (uint8_t *)"数据溢出", 10,0xFFFF); 	
		}
		else
		{
			esp8266_buf[esp8266_cnt++] = a_esp8266_buf;   //接收数据转存
		}
			HAL_UART_Receive_IT(&ESP_UART, (uint8_t *)&a_esp8266_buf, 1);   //再开启接收中断
	}
	
	//防止多次RECeive接收不到，出现错误

}
