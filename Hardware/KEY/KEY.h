#ifndef _KEY_H
#define _KEY_H

// MCU型号
#include "stm32f10x.h"

// 外置硬件
#include "GPIO.h"

// RTOS头文件
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "MyTASK.h"

// 变量
extern uint8_t KEY1_State;
extern uint8_t KEY2_State;
extern uint8_t KEY3_State;
extern uint8_t KEY4_State;

// API
void KEY_InitPro(void);
void KEY1_Scanf(void);
void KEY2_Scanf(void);
void KEY3_Scanf(void);
void KEY4_Scanf(void);
void KEY_KEYScanf_Disable(void);
void KEY_KEYScanf_Enable(void);

#endif
