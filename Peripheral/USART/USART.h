#ifndef _USART_H_
#define _USART_H_

// 标准库
#include "string.h"
#include "stdio.h"
#include "stdarg.h"

// MCU型号
#include "stm32f10x.h"

// 变量
extern uint8_t USART3_RecFlag;
extern uint8_t USART1_RecFlag;
extern uint8_t USART3_RecBuffer[1024];
extern uint8_t USART1_RecBuffer[1024];

// 宏定义

// API
void USART_InitPro(void);
void USART1_Clear_RecBuffer(void);
void USART3_Clear_RecBuffer(void);
void USART1_SendByte(uint16_t Byte);
void USART3_SendByte(uint16_t Byte);
void USART1_SendString(uint8_t *String);
void USART3_SendString(uint8_t *String);
void USART1_SendNumber(int32_t Number);
void USART3_SendNumber(int32_t Number);
void USART_SendString_Wireless(uint8_t *String);
void USART_SendNumber_Wireless(int32_t Number);
void USART_SendString_Computer(uint8_t *String);
void USART_SendNumber_Computer(int32_t Number);
void USART1_RecState(void);
void USART3_RecState(void);

#endif
