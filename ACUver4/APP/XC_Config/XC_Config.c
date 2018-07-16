/**
  ******************************************************************************
  * @file    XC_Config.c
  * @author  XC_
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨: STM32 ������ 
  * 
  ******************************************************************************
  */
#include "XC_Config.h"

/**
 * ��������NVIC_Configuration
 * ����  ������NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
 void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
//		EXTI_InitTypeDef EXTI_InitStructure;
	
    /* Configure one bit for preemption priority */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO/*�ڶ�����*/, ENABLE);    //���ܸ���IOʱ��
	
	  /* ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
												
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//TIM2ȫ���ж�	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ��
    NVIC_Init(&NVIC_InitStructure);//��ʼ��
	
	  //�жϷ����ʼ��
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//���ڽ����ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	             
		NVIC_Init(&NVIC_InitStructure);	
		
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//���ڽ����ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	             
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//���ڽ����ж�
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
