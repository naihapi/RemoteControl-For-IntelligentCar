#ifndef _Flash_H
#define _Flash_H

// MCU型号
#include "stm32f10x.h"

// 宏定义
#define Flash_Address_EndPage 0x0800FC00 // 这个是FLASH最后一页的起始地址
#define Flash_DataLength 512

// 变量
extern uint16_t FlashData[Flash_DataLength];
extern uint8_t State_OLEDMode;

// 软件
#include "Menu.h"

// API
void FLash_InitPro(void);
void Flash_SavaData(void);

#endif
