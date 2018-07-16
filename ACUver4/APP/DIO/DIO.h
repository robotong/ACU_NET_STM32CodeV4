#ifndef __DIO_H
#define __DIO_H 

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "MyMap.h"
/*
GPIOx 			GPIOA ... GPIOE
GPIO_Pin		GPIO_Pin_0 ... GPIO_Pin_15
GPIO_Mode 	GPIO_Mode_AIN,GPIO_Mode_IN_FLOATING,GPIO_Mode_IPD,GPIO_Mode_IPU,GPIO_Mode_Out_OD,
						GPIO_Mode_Out_PP,GPIO_Mode_AF_OD,GPIO_Mode_AF_PP
GPIO_Speed 	  GPIO_Speed_10MHz,GPIO_Speed_2MHz,GPIO_Speed_50MHz

e.g. DIO_Initial(GPIOA, GPIO_Pin_0,GPIO_Mode_Out_PP,GPIO_Speed_10MHz);
*/



void Input_Init(void);
unsigned int GetInputData(void);

void SystemStateDisplay(DeviceRegister__TypeDef *device_acu);

#endif



