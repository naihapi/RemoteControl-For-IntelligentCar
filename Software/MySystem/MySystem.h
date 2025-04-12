#ifndef _MySystem_H
#define _MySystem_H

// MCU型号
#include "stm32f10x.h"

// 外置硬件
#include "OLED.h"

// 软件
#include "Menu.h"
#include "Build.h"

// API
void MySystem_OLED_Function(void);
void MySystem_GetFreeHeap(void);

#endif
