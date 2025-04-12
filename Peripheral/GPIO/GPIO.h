#ifndef _GPIO_H
#define _GPIO_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "TIM.h"

// API
void GPIO_InitPro(void);
void GPIO_LED_ON(void);
void GPIO_LED_OFF(void);
uint8_t GPIO_RetState_KEY1(void);
uint8_t GPIO_RetState_KEY2(void);
uint8_t GPIO_RetState_KEY3(void);
uint8_t GPIO_RetState_KEY4(void);

#endif
