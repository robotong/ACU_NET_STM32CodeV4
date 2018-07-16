#include "DIO.h"
#include "stm32f10x.h"

#include "RESISTER.h"
#include "MyMap.h"

#define LED_GPIO_CLK   RCC_APB2Periph_GPIOC 
//#define LED_PORT   	   GPIOC
#define LED_PIN        GPIO_Pin_13

u16   timeMs_LED; 


//״̬��ʾ����ʾ�ж�
void StateDisplay(void)
{
	System_State|=0x01;//ϵͳ�������У���һ���Ƴ���
	//500ms��˸
	if(timeMs_LED<500)
	{
		System_State|=0x08;//1000������
		if(SensorLeaveFlag==1)
			System_State|=0x02;//0010�ڶ�����ʾ����������״̬
		else
			System_State&=0x0D;//1101�ڶ�����ʾ����������״̬
	}
	else if(timeMs_LED>500)
	{
			System_State&=0x0D;
			System_State&=~(0x08);
	}
}


void SystemStateDisplay(DeviceRegister__TypeDef *device_acu)
{
	//System_State|=0x01;//ϵͳ�������У���һ���Ƴ���
	//500ms��˸
	if(timeMs_LED<500)
	{
		device_acu->device.LED_State.bits.systemrun = 1;  //����״̬����˸-��
		System_State|=0x08;//1000������
		if(SensorLeaveFlag==1)
			device_acu->device.LED_State.bits.sensorerror=1;//���ĵ���ʾ����������״̬
		else
			device_acu->device.LED_State.bits.sensorerror=0;//���ĵ���ʾ����������״̬
	}
	else if(timeMs_LED>500)
	{
		device_acu->device.LED_State.bits.systemrun = 0;	//����״̬����˸-��
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


