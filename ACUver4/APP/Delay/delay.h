#ifndef _DELAY_H
#define _DELAY_H

#include "XC_Config.h"

void Delay_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 Nus);
void TIM2_Configuration(void);

#endif

