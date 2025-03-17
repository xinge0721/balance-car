#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include <stdio.h>
#include "stm32f10x.h"                  // Device header

void u3_Init(void);
void u3_SendByte(uint8_t Byte);
void u3_SendArray(uint8_t *Array, uint16_t Length);
void u3_SendString(char *String);
void u3_SendNumber(uint32_t Number, uint8_t Length);
void u3_Printf(char *format, ...);

uint8_t u3_GetRxFlag(void);
uint8_t u3_GetRxData(void);
extern uint8_t u3_RxBuf[8];
#endif	   
















