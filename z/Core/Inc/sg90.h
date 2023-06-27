#ifndef _SG90_H_
#define _SG90_H_

#include "main.h"
#include "tim.h"
#include "gpio.h"

#define Degrees_0    50 //ԭ��λ��
#define Degrees_45	100 //45��λ��
#define Degrees_90   150//90��λ��
#define Degrees_135  200 //135��λ��
#define Degrees_180  250 //180��λ��

extern uint8_t DuojiLock;
extern uint8_t Duoji_Mode;
void SG90_Rotate(uint16_t Degrees);
void SG90_Mode(uint16_t Sudu);
#endif
