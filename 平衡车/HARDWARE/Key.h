#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

void Key_Init(void);
uint8_t Get_Key1Num(void);
extern  int Keyflag;
#endif
