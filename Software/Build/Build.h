#ifndef _Build_H
#define _Build_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "UI.h"
#include "Menu.h"
#include "MyTASK.h"

// 外置硬件
#include "KEY.h"

// 变量
extern uint8_t Build_NowPage;
// extern MenuItem *Build_NowMenuItem;

// API
void Build_InitPro(void);
void Build_ControlPro(void);
void Build_RequestUpdateControl_KEYevent(void);
void Build_ModuleControl_RealTime_Handle(void);

#endif
