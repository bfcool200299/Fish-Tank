#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "main.h"
#include <stdio.h>
#define  DS18B20_DQ_OUT_HIGH       HAL_GPIO_WritePin(DQ_GPIO_Port, DQ_Pin, GPIO_PIN_SET)
#define  DS18B20_DQ_OUT_LOW        HAL_GPIO_WritePin(DQ_GPIO_Port, DQ_Pin, GPIO_PIN_RESET)
#define  DS18B20_DQ_IN             HAL_GPIO_ReadPin(DQ_GPIO_Port, DQ_Pin)

float Ds18b20_Get_Temp(void);
#endif
