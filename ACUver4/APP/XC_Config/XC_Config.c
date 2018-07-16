/**
  ******************************************************************************
  * @file    XC_Config.c
  * @author  XC_
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台: STM32 开发板 
  * 
  ******************************************************************************
  */
#include "XC_Config.h"

/**
 * 函数名：NVIC_Configuration
 * 描述  ：设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
 void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
//		EXTI_InitTypeDef EXTI_InitStructure;
	
    /* Configure one bit for preemption priority */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO/*第二功能*/, ENABLE);    //功能复用IO时钟
	
	  /* 设置NVIC中断分组2:2位抢占优先级，2位响应优先级 */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
												
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//TIM2全局中断	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//从优先级	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能
    NVIC_Init(&NVIC_InitStructure);//初始化
	
	  //中断分组初始化
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口接收中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	             
		NVIC_Init(&NVIC_InitStructure);	
		
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口接收中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	             
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口接收中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	             
		NVIC_Init(&NVIC_InitStructure);

}


void GPIO_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;					
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  	
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}




//*************************************************************************************************************************************
