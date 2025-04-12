#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"
#include "GPIO.h"

extern uint8_t Delay_Flag;

void TIM2_Delay_ms(uint16_t xms);
void TIM2_Delay_s(uint16_t xs);

#endif
