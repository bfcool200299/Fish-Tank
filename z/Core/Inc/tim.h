/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "sg90.h"
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim4;

/* USER CODE BEGIN Private defines */
extern uint32_t Time_Duo;//¶æ»ú¼ÆÊý
extern uint8_t HUNZHUOFlag;
extern uint8_t Ds18b20Flag;
extern uint8_t BH1750Flag;
extern uint8_t	LanYaFlag;
extern uint8_t RGB1sFlag;
extern uint8_t TDSFlag;
extern uint8_t RGB20msFlag;
extern uint8_t D_Mode_1;
extern uint8_t D_Mode_2;
extern uint8_t D_Mode_3;
extern uint8_t D_Mode_4;
extern uint8_t D_Mode_5;
extern uint8_t D_Mode_6;
/* USER CODE END Private defines */

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
void Delay_Us(unsigned int us_time);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

