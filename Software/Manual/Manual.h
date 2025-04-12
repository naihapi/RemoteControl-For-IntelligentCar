#ifndef _Manual_H
#define _Manual_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "UI.h"
#include "Build.h"
#include "Update.h"

// 外设
#include "GPIO.h"

// API
void Manual_CustomFunction(void);
void Manual_TurnState_UpdateToCar(void);

#endif
