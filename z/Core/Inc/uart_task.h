#ifndef _UART_TASK_H_
#define _UART_TASK_H_


#include <stdio.h>
#include "main.h"
#include "my_printf.h"
#include "usart.h"
extern uint8_t usart_screen;
extern uint8_t RGBStaus;
extern uint8_t RGBLcok;
void HMI_Printf_F_WenDu(uint32_t val,uint32_t vvs);
void HMI_Printf_F_GuangZhao(uint32_t val,uint32_t vvs);
void HMI_Printf_F_TDS(uint32_t val,uint32_t vvs);
void HMI_Printf_F_HunZhuo(uint32_t val,uint32_t vvs);
uint32_t Decimal_1(float DataP);
uint32_t Decimal_2(float DataP);
void DuojiTask(void);

enum Screen
{
	ShuiOpen = 0x11,
	ShuiOff = 0x12,
	JiaReOpen = 0x13,
	JiaReOff = 0x14,
	ZhiYangOpen = 0x15,
	ZhiYangOff = 0x16,
	DengGuangOn = 0x17,
	DengGuangOff = 0x18,
	RGBOn = 0x19,
	RGBOff = 0x20,
	Raninbow = 0x21,
	Sea = 0x22,
	Sengling = 0x23,
	HuangMo = 0x24,
	ChouShuiOn = 0x25,
	ChouShuiOff = 0x26,
	FeedOne = 0x27,
	FeedTwo = 0x28,
	FeedThree = 0x29,
	FeedFour = 0x30,
	FeedFive = 0x31,
	FeedSix = 0x32,
};
#endif
