#ifndef _MAIN_H
#define _MAIN_H

// 标准库
#include "stdio.h"
#include "stdbool.h"

// MCU型号
#include "stm32f10x.h"

// RTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "MyTASK.h"

// 外置硬件
//...

// 宏定义
//...

// 软件
#include "UI.h"
#include "Delay.h"
#include "Build.h"

// 外设
#include "GPIO.h"
#include "TIM.h"
#include "Flash.h"

#endif
