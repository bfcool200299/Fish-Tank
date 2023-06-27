#ifndef _WS2812B_H_
#define _WS2812B_H_
#include "stdint.h"
#include "main.h"

#define ONE_PULSE        (125)                           //1 ��
#define ZERO_PULSE       (62)                           //0 ��
#define RESET_PULSE      (80)                           //80 ����λ�ź�
#define LED_NUMS         (30)                            //led ����
#define LED_DATA_LEN     (24)                           //led ���ȣ�������Ҫ24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812������Ҫ�����鳤��

extern uint16_t  RGB_buffur[RESET_PULSE + WS2812_DATA_LEN];

void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num);
void ws2812_init(uint8_t led_nums);
void ws2812_example(void);
 void ws2812_blue(uint8_t led_nums);
 void ws2812_red(uint8_t led_nums);
 void ws2812_green(uint8_t led_nums);
void ModeFirst(void);
void ModeThird(void);
void ModeSecond(void);
void Mode_RaninBow(void);
void OFFRGB(void);
#endif
