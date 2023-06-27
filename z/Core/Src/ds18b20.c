#include "tim.h"
#include "DS18B20.h"

//�¶ȴ����� DQ�ӵ�PA4

/****************************************************************************
��������DS18B20_IO_IN
���ܣ�ʹDS18B20_DQ���ű�Ϊ����ģʽ
���룺��
�������
����ֵ����
��ע��DQ����ΪPA5
****************************************************************************/
void DQ_GPIO_IN(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
}


/****************************************************************************
��������DS18B20_IO_OUT
���ܣ�ʹDS18B20_DQ���ű�Ϊ�������ģʽ
���룺��
�������
����ֵ����
��ע��DQ����ΪPA4
****************************************************************************/
void DQ_GPIO_OUT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/**
 * @brief  DS18B20 ��λ
 * @param  ��
 * @return ��
 * @note ���������� 480us - 960us ������λ��Ȼ��ȴ� 15us ����������
 */
void Ds18b20_Reset(void)
{
	//���ģʽ��
	DQ_GPIO_OUT();
	
	//�������� 750us
	DS18B20_DQ_OUT_LOW;
	Delay_Us(750);
	
	//�ͷ����ߣ��ȴ���������
	DS18B20_DQ_OUT_HIGH;
	Delay_Us(15);
}
/**
 * @brief  ����������	
 * @param  ��
 * @return   ��������: 0 
 *         ����������: 1
 */
uint8_t Ds18B20_CheckPulse(void)
{
	/* ��ʱ���������豸�����ڣ���Ҫ�˳�������һֱ�ȴ� */
	uint8_t Time_Count = 0;
	
	//�� GPIO �ĳ�����ģʽ��
	DQ_GPIO_IN();
	
	/* ��Ӧʱ���е� DS18B20 �ȴ� (15 - 60)us */
	while (DS18B20_DQ_IN && Time_Count < 100)
	{
		Time_Count++;
		Delay_Us(1);
	}
	
	/* �Ѿ���ȥ�� 100us �������廹û�����������豸������ */
	if (Time_Count >= 100)
		return 1;   
	/* ���嵽������λ��ʱ���� */
	else
		Time_Count = 0;
	
	/* ��Ӧʱ���е� DS18B20 �������� (60 - 240)us */
	while (!DS18B20_DQ_IN && Time_Count < 240)
	{
		Time_Count++;
		Delay_Us(1);
	}
	
	/* ��ʱ��ͼ��֪��������������ó��� 240us */
	if (Time_Count >= 240)
		return 1;
	else
		return 0;    //��⵽��������
}
/**
 * @brief  ��ȡ1bit���� 
 * @param  ��
 * @return ��ȡ��1Bit������
 * @note   �Ƚ��������� 15us �󣬶�ȡ����״̬
 */ 
uint8_t Ds18b20_Read_Bit(void)
{
	uint8_t dat;
	//���ģʽ
	DQ_GPIO_OUT();
	
	//���������� 15us ���ȡ����״̬
	DS18B20_DQ_OUT_LOW;
	Delay_Us(15);
	
	//����Ҫ��ȡ����ֵ�����������ó�����ģʽ
	DQ_GPIO_IN();
	
	if (DS18B20_DQ_IN == SET)
		dat = 1;
	else
		dat = 0;
	
	//��ȡ�������� 60us
	Delay_Us(50);
	
	return dat;
}
/** 
 * @brief  �� DS18B20 �϶�ȡ 1Byte
 * @param  ��
 * @return ������8λ����
 * @note   ��λ����λ
 */
uint8_t Ds18B20_Read_Byte(void)
{
	uint8_t data = 0x00,mask;
	
	for (mask = 0x01;mask != 0;mask <<= 1)
	{
		if (Ds18b20_Read_Bit() == SET)
			data |= mask;
		else
			data &= ~mask;
	}
	
	return data;
}

/**
 * @brief  д��һ�ֽ����ݣ���λ����
 * @param  data д������� 
 * @return ��
 * @note  д0: ��ʱ��ͼ��֪�������������� 60us ��ʾд 0
          д1: ��ʱ��ͼ��֪���������ߴ��� 1us ����С�� 15us �󣬽������������ߣ���ʱ�䳬�� 60us
          д���ڱ����� 1us �Ļָ�ʱ��
 */
void Ds18B20_Write_Byte(uint8_t data)
{
	uint8_t mask;
	
	for (mask = 0x01;mask != 0;mask <<= 1)
	{
		DQ_GPIO_OUT();
		
		//д0
		if ((data & mask) == RESET)
		{
			/* ������������ 60us */
			DS18B20_DQ_OUT_LOW;
			Delay_Us(70);
			
			//2us �Ļָ�ʱ��
			DS18B20_DQ_OUT_HIGH;
			Delay_Us(2);
		}
		else  //д1
		{
			/* �������ߴ��� 1us ����С�� 15us */
			DS18B20_DQ_OUT_LOW;
			Delay_Us(9);
			
			/* �������ߣ���ʱ�䳬�� 60us */
			DS18B20_DQ_OUT_HIGH;
			Delay_Us(55);
		}
	}
}
/**
 * @brief  ��ȡ�¶�
 * @param  ��
 * @return ��DS18B20�϶�ȡ�����¶�ֵ
 * @note   �˻�ȡ����Ϊ���� ROM ��ȡ,�ʺ���������ֻ��һ���豸
 */
float Ds18b20_Get_Temp(void)
{
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	Ds18b20_Reset();	   
	Ds18B20_CheckPulse();	 
	Ds18B20_Write_Byte(0xCC);				         /* ���� ROM */
	Ds18B20_Write_Byte(0x44);				     /* ��ʼת�� */
	
	Ds18b20_Reset();	   
	Ds18B20_CheckPulse();	 
	Ds18B20_Write_Byte(0xCC);				        /* ���� ROM */
	Ds18B20_Write_Byte(0xBE);				/* ���¶�ֵ */
	
	tplsb = Ds18B20_Read_Byte();		 
	tpmsb = Ds18B20_Read_Byte(); 
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	f_tem = s_tem * 0.0625-3;
	if(f_tem)
	return f_tem;
	else
		return f_tem;
	
}

