#ifndef _UI_H
#define _UI_H

// MCU型号
#include "stm32f10x.h"

// 外置硬件
#include "OLED.h"

// 软件
#include "MyTASK.h"
#include "Menu.h"

// RTOS头文件
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

// API
void UI_InitPro(void);
void UI_Display_SwitchModule(uint8_t *Title, uint8_t *State);
void UI_Display_ViewModule(uint8_t *Title, uint8_t *Description, int *Value);
void UI_Display_SliderModule(uint8_t *Title, int *NowValue, int *MaxValue, int *MiniValue, uint8_t *Unit, uint8_t Selected);
// void UI_Display_Home(uint8_t selected, MenuHome *head);
// void UI_Display_Menu(uint8_t selected, MenuItem *head, uint8_t maxitem);
void UI_Display_Requesting(void);
void UI_Display_RequestSuccess(void);
void UI_Display_RequestFail(void);
void UI_Display_Uploading(void);
void UI_Display_UpdateSuccess(void);
void UI_Display_UpdateFail(void);
void UI_Display_ManualControl(uint8_t left, uint8_t right, uint8_t front, uint8_t rear);
void UI_Display_ExitTips(void);
void UI_Display_TipsInto(void);
void UI_Display_TipsFail(void);

#endif
