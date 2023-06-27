#ifndef _SG90_H_
#define _SG90_H_

#include "main.h"
#include "tim.h"
#include "gpio.h"

#define Degrees_0    50 //原点位置
#define Degrees_45	100 //45度位置
#define Degrees_90   150//90度位置
#define Degrees_135  200 //135度位置
#define Degrees_180  250 //180度位置

extern uint8_t DuojiLock;
extern uint8_t Duoji_Mode;
void SG90_Rotate(uint16_t Degrees);
void SG90_Mode(uint16_t Sudu);
#endif
