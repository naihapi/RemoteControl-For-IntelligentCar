#ifndef _Update_H
#define _Update_H

// MCU型号
#include "stm32f10x.h"

// 标准库
#include "string.h"

// 外置硬件
#include "CC2530.h"

// API
void Update_InitPro(void);
uint8_t Update_SwitchModule(uint8_t *name, uint8_t *state);
uint8_t Update_SliderModule(uint8_t *name, int *now, int *max, int *mini);
uint8_t Update_Currency(uint8_t *name, uint8_t length, uint8_t **arr, uint8_t *check);

#endif
