#ifndef _DATATASK_H_
#define _DATATASK_H_
#include "main.h"
#include <stdio.h>

extern uint8_t Switch_JiaRe;  //���ȿ���
extern uint8_t Switch_ZhiO2;  //��������
extern uint8_t Switch_DengGuang; //�ƹ⿪��
extern uint8_t Switch_Guolv;   //���˿���
extern float Temperature; //ds18b20�¶�

uint32_t DS18b20Task(void);
void DataTask(void);
uint32_t DS18b20Task(void);
uint16_t BH1750_TASK(void);
uint32_t HunZhuo_Task(void);
uint32_t TDS_Task(void);
#endif
