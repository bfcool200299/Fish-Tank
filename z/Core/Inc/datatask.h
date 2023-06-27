#ifndef _DATATASK_H_
#define _DATATASK_H_
#include "main.h"
#include <stdio.h>

extern uint8_t Switch_JiaRe;  //加热开关
extern uint8_t Switch_ZhiO2;  //制氧开关
extern uint8_t Switch_DengGuang; //灯光开关
extern uint8_t Switch_Guolv;   //过滤开关
extern float Temperature; //ds18b20温度

uint32_t DS18b20Task(void);
void DataTask(void);
uint32_t DS18b20Task(void);
uint16_t BH1750_TASK(void);
uint32_t HunZhuo_Task(void);
uint32_t TDS_Task(void);
#endif
