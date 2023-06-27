#include "datatask.h"
#include "ds18b20.h"
#include "uart_task.h"
#include "tim.h"
#include "bh1750.h"
#include "adc.h"
#include "MQTT_Conf.h"
#include "lanya.h"
#include "sg90.h"
#include "ws2812b.h"

#define N 12

uint8_t TData[4];
float Temperature; //ds18b20温度
uint8_t Switch_JiaRe;
uint8_t Switch_ZhiO2;
uint8_t Switch_DengGuang;
uint8_t Switch_Guolv;

uint32_t DS18b20Task(void)
{
	uint32_t temperature = 0;
	Temperature = Ds18b20_Get_Temp();
  temperature = Decimal_1(Temperature);
	return temperature;
 }

uint16_t BH1750_TASK(void)
{
	uint8_t dat[2] = {0}; 
	
	BH1750_Send_Cmd(ONCE_H_MODE);
  BH1750_Read_Dat(dat);
	return BH1750_Dat_To_Lux(dat);
}
//浊度算法 就ADC转换一个
//ADCA IN5
//SCL = PA5;SDA = PB7
uint32_t HunZhuo_Task(void)
{
	uint32_t Zhuodu = 0;
	float volt_ADC;
	float temp;
	
	HAL_ADC_Start(&hadc1); //启动ADC单次转换
	HAL_ADC_PollForConversion(&hadc1, 50); //等待ADC转换完成
	volt_ADC = (float)HAL_ADC_GetValue(&hadc1)/4096*3.3; //读取ADC转换数据
	temp = volt_ADC*100/3.3;
	if(temp > 100) 
		{
			temp = 95;
		}
	
		Zhuodu = 10000-Decimal_2(temp)+500; //放大了100
		if(Zhuodu >10000)
		{
			Zhuodu = 10000;
		}
		
		TData[2] = ((100-(uint8_t)temp)/10%10);
	  TData[3] = ((100-(uint8_t)temp)%10);
		
		return Zhuodu;	
}
uint32_t TDS_Task(void)
{
	uint32_t TDS_VALUE;
	
	float TDS_voltage;
	float TDS_value=0.0;
	float temp_data=0.0;
	float compensationCoefficient=1.0;//温度校准系数
	float compensationVolatge;
	float kValue=1.5;
	float smoke_value = 0;
	
  	HAL_ADC_Start(&hadc2); //启动ADC单次转换
		HAL_ADC_PollForConversion(&hadc2, 50); //等待ADC转换完成
		smoke_value = (float)HAL_ADC_GetValue(&hadc2)/4096*3.3; //读取ADC转换数据
	
		TDS_voltage=(float)smoke_value;
		compensationCoefficient=1.0+0.02*((temp_data/10)-25.0); 
	compensationVolatge=TDS_voltage/compensationCoefficient;
		
	TDS_value=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 
	255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5*kValue;
		
	
	  if((TDS_value<=0)){TDS_value=0;}
		if((TDS_value>1400)){TDS_value=1400;}
		
		TDS_VALUE = (uint32_t)TDS_value;
		return TDS_VALUE;
}
void DataTask(void)
 {
	 unsigned char nowtemp; //当前按键值
	 //喂食调速
	 SG90_Mode(30);
	 	//蓝牙处理模块
	 if(LanYaFlag == 1 && RX_flag == 1)
	 {
		 LanYaFlag = 0;RX_flag = 0;
		 
		 uart2_printf("I got the message %c",RxBuffer);
		 
		 switch(RxBuffer[0] )
		 {
			 case 10:
				 HAL_GPIO_TogglePin(GPIOA,GuoLv_Pin);
				 nowtemp = HAL_GPIO_ReadPin(GPIOA,GuoLv_Pin);
				 printf("shuibeng.bt0.val=%d",nowtemp); //发送数值
         printf("\xff\xff\xff"); //发送结束符
				 break;
			 case 11:
				 HAL_GPIO_TogglePin(GPIOA,LED_Pin);
			   nowtemp = HAL_GPIO_ReadPin(GPIOA,LED_Pin);
				 printf("light.bt0.val=%d",nowtemp); //发送数值
         printf("\xff\xff\xff"); //发送结束符
				 break;
			 case 12:
				 HAL_GPIO_TogglePin(GPIOA,MadeO2_Pin);
			   nowtemp = HAL_GPIO_ReadPin(GPIOA,MadeO2_Pin);
				 printf("shuibeng.bt2.val=%d",nowtemp); //发送数值
         printf("\xff\xff\xff"); //发送结束符
				 break;
			 case 13:
				 HAL_GPIO_TogglePin(GPIOB,JiaRe_Pin);
			   nowtemp = HAL_GPIO_ReadPin(GPIOB,JiaRe_Pin);
				 printf("shuibeng.bt1.val=%d",nowtemp); //发送数值
         printf("\xff\xff\xff"); //发送结束符
				 break;
		 }
	
			 for(uint8_t i=0;i<20;i++)  //清除接收的标志
					{
							RxBuffer[i] = 0;
					}
	 }
	 //RGB处理
	 if(RGBLcok == 1)
	 {
		 switch(RGBStaus)
		 {
			 case 1:
				 Mode_RaninBow();
				 break;
			 
			 case 2:
				 ModeFirst();
				 break;
			 
			 case 3:
				 ModeSecond();
				 break;
			 
			 case 4:
				 ModeThird();
				 break;
		 }
	 }else if(RGBLcok == 0)
	 {
		 OFFRGB();
	 }
	 //温度处理模块
	 if(Ds18b20Flag == 1)
	 {
		 TData[0] = (uint8_t)Ds18b20_Get_Temp()/10%10;
	   TData[1] = (uint8_t)Ds18b20_Get_Temp()%10;

		 uart3_printf("%d",TData[0]);
		 uart3_printf("%d",TData[1]);
		 uart3_printf("%d",TData[2]);
		 uart3_printf("%d",TData[3]);
		 Ds18b20Flag = 0;
		 HMI_Printf_F_WenDu(DS18b20Task(),1);
		 if(DS18b20Task() < 200)
		 {
			 
		 }
	 }
//光照	 
	 if(BH1750Flag == 1)
	 {
		 BH1750Flag = 0;
		 uart2_printf("%d\r\n",BH1750_TASK());
		 HMI_Printf_F_GuangZhao(BH1750_TASK(),0);
		if(BH1750_TASK()<15)
		{
			
		}
	 }
//浑浊度
	 if(HUNZHUOFlag == 1)
	 {
		 HUNZHUOFlag = 0;
		 HMI_Printf_F_HunZhuo(HunZhuo_Task(),2);
	 }
	 
	 if(TDSFlag == 1)
	 {
		 TDSFlag = 0;
		 HMI_Printf_F_TDS(TDS_Task(),0);
	 }
 }
 