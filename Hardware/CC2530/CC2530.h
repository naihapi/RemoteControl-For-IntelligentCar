#ifndef _CC2530_H
#define _CC2530_H

// MCU型号
#include "stm32f10x.h"

// 标准库
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// 外设
#include "USART.h"

// RTOS头文件
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

// API
void CC2530_InitPro(void);
uint8_t CC2530_Command(uint8_t *string, uint8_t *cmd);
uint8_t CC2530_CommandPRO(uint8_t *string, uint8_t *cmd);
uint8_t CC2530_CommandSE(uint8_t *string, uint8_t *cmd);

#endif
