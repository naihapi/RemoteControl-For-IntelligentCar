#ifndef _TIM_H
#define _TIM_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "Delay.h"

// 变量
extern uint8_t TIM3_CountFinish;

// API
void TIM_InitPro(void);

#endif
