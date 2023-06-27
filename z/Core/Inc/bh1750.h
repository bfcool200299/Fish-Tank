#ifndef _BH1750_H_
#define _BH1750_H_

#include "main.h"


#define BH1750_ADDR_WRITE 0x46
#define BH1750_ADDR_READ 0x47

typedef enum
{
	POWER_OFF_CMD = 0x00,
	POWER_ON_CMD = 0X01,
	RESET_REGISTER = 0X07,
	CONT_H_MODE = 0X10,
	CONT_H_MODE2 = 0X11,
	CONT_L_MODE = 0X13,
	ONCE_H_MODE = 0X20,
	ONCE_H_MODE2 = 0X21,
	ONCE_L_MODE = 0X23,
}BH1750_MODE;

uint8_t  BH1750_Send_Cmd(BH1750_MODE cmd);
uint8_t  BH1750_Read_Dat(uint8_t* dat);
uint16_t BH1750_Dat_To_Lux(uint8_t* dat);

#endif
