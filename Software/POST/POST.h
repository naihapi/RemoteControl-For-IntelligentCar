#ifndef _POST_H
#define _POST_H

// MCU型号
#include "stm32f10x.h"

// 标准库
#include "string.h"

// 外置硬件
#include "CC2530.h"
#include "OLED.h"

// 变量
//...

// API
void POST_InitPro(void);
uint8_t POST_SwitchModule(uint8_t *name, uint8_t *state);
uint8_t POST_ViewModule(uint8_t *name, int *state);
uint8_t POST_SliderModule(uint8_t *name, int *nowvalue, int *maxvalue, int *minivalue);
uint8_t POST_Currency(uint8_t *name, uint8_t length, uint8_t **arr, uint8_t *check);

#endif
