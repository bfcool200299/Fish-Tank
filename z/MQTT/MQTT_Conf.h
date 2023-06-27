/***********************************************************************************************
* ESP8266 ����MQTT�����ļ�
* �˿�ռ�����£�
* 1��һ��GPIO��λ����
* 2��һ������
* 3��3V3 ��GND
* ʹ��˵�����£�
* 1�����ĸ�λ���ź�ѡ���Ĵ���
* 2�������Լ��Ĵ����ض���
* 3���������ĺͷ���������
* 4�������豸ID��Ϣ
* 5������wife�����MQTT������
* 6������ ESP8266_LINK_Init()���Ӻ���
* 7�������������esp8266.h��onenet.h�ĺ���
************************************************************************************************/


#ifndef	__MQTT_CONF_H
#define __MQTT_CONF_H

#include "stdio.h"
#include "string.h"
#include "my_printf.h"
#include "onenet.h"
#include "Common.h"
#include "esp8266.h"
#include "mqttkit.h"

#include "cJSON.h"

#include "main.h"


#define ESP8266_REST_Pin GPIO_PIN_5                    //��λ��������ΪPA5 
#define ESP8266_REST_GPIO_Port GPIOA

#define ESP_UART huart3                                //esp8266��ͨ�Ŵ���

#define USER_PRINTF uartx_printf                             //�����û��Լ��Ĵ����ض�����

#define SUB_TOPIC "lls_app_v0_dssds" //�������⣨��Ҫ�����ţ�

#define PUB_TOPIC "Taaddfgsds" //��������

#define PROID		"4ddw4sdSAndsm"                       //�豸ID������㣩

#define AUTH_INFO	"1dd1deSDdsdsd332441"                              //���� ������㣩

#define DEVID		"74dsddswqr946"                        //������㣩

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"dianke516\",\"dianke516\"\r\n"    //TP-LINK_5D25��wife���� 18296885326��wife����

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtt.llsmqttport.xyz\",1883\r\n"//broker-cn.emqx.io ��mqtt��������ַ��1883�Ƕ˿ں�




extern unsigned char a_esp8266_buf;                   //ESP8266 01s����ͨ�Ż�����

//esp8266���ӳ�ʼ��
#define ESP8266_LINK_Init() \
do { \
        HAL_UART_Receive_IT(&ESP_UART, (uint8_t *)&a_esp8266_buf, 1);\
        ESP8266_Init();\
        while (OneNet_DevLink())\
            {\
               HAL_Delay(500);\
            }\
  } while(0U)



	
#endif
































