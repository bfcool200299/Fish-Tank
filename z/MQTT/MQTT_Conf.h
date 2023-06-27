/***********************************************************************************************
* ESP8266 连接MQTT配置文件
* 端口占用如下：
* 1：一个GPIO复位引脚
* 2：一个串口
* 3：3V3 和GND
* 使用说明如下：
* 1：更改复位引脚和选定的串口
* 2：更换自己的串口重定向
* 3：更换订阅和发布的主题
* 4：配置设备ID信息
* 5：配置wife密码和MQTT服务器
* 6：调用 ESP8266_LINK_Init()连接函数
* 7：根据所需调用esp8266.h和onenet.h的函数
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


#define ESP8266_REST_Pin GPIO_PIN_5                    //复位引脚设置为PA5 
#define ESP8266_REST_GPIO_Port GPIOA

#define ESP_UART huart3                                //esp8266的通信串口

#define USER_PRINTF uartx_printf                             //定义用户自己的串口重定向函数

#define SUB_TOPIC "lls_app_v0_dssds" //订阅主题（需要加引号）

#define PUB_TOPIC "Taaddfgsds" //发布主题

#define PROID		"4ddw4sdSAndsm"                       //设备ID（可随便）

#define AUTH_INFO	"1dd1deSDdsdsd332441"                              //密码 （可随便）

#define DEVID		"74dsddswqr946"                        //（可随便）

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"dianke516\",\"dianke516\"\r\n"    //TP-LINK_5D25是wife名称 18296885326是wife密码

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtt.llsmqttport.xyz\",1883\r\n"//broker-cn.emqx.io 是mqtt服务器地址，1883是端口号




extern unsigned char a_esp8266_buf;                   //ESP8266 01s串口通信缓冲区

//esp8266连接初始化
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
































