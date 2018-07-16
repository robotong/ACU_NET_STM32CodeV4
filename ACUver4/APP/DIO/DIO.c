#include "DIO.h"
#include "stm32f10x.h"

#include "RESISTER.h"
#include "MyMap.h"

#define LED_GPIO_CLK   RCC_APB2Periph_GPIOC 
//#define LED_PORT   	   GPIOC
#define LED_PIN        GPIO_Pin_13

u16   timeMs_LED; 


//状态显示灯显示判断
void StateDisplay(void)
{
	System_State|=0x01;//系统正常运行，第一个灯常亮
	//500ms闪烁
	if(timeMs_LED<500)
	{
		System_State|=0x08;//1000第三灯
		if(SensorLeaveFlag==1)
			System_State|=0x02;//0010第二灯显示传感器离线状态
		else
			System_State&=0x0D;//1101第二灯显示传感器离线状态
	}
	else if(timeMs_LED>500)
	{
			System_State&=0x0D;
			System_State&=~(0x08);
	}
}


void SystemStateDisplay(DeviceRegister__TypeDef *device_acu)
{
	//System_State|=0x01;//系统正常运行，第一个灯常亮
	//500ms闪烁
	if(timeMs_LED<500)
	{
		device_acu->device.LED_State.bits.systemrun = 1;  //运行状态灯闪烁-灭
		System_State|=0x08;//1000第三灯
		if(SensorLeaveFlag==1)
			device_acu->device.LED_State.bits.sensorerror=1;//第四灯显示传感器离线状态
		else
			device_acu->device.LED_State.bits.sensorerror=0;//第四灯显示传感器离线状态
	}
	else if(timeMs_LED>500)
	{
		device_acu->device.LED_State.bits.systemrun = 0;	//运行状态灯闪烁-亮
		System_State&=0x0D;
		System_State&=~(0x08);
	}

}

void Input_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

}	

unsigned int GetInputData(void)
{
	unsigned int inputState=0,temp1;
	
	temp1=GPIOB->IDR;
	
	//inputState=(temp1&0x0007);
	//inputState|=((temp1&0xFC00)>>7);
	inputState=(~temp1)&0x0000FFFF;
	return inputState;

	
}


