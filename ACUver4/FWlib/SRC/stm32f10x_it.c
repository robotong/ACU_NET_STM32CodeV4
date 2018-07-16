/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "string.h"
#include "XC_Config.h"

#define BUG
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t TimeDisplay;


#ifdef _infrared_H
extern u32 hw_data;
extern u8 flag_hw_data;
extern u8 hy_jssj(void);
#endif

//static u8 Temp[11];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval : None
  */
void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		/* Clear the RTC Second interrupt */
		RTC_ClearITPendingBit(RTC_IT_SEC);
	
		/* Enable time update */
		TimeDisplay = 1;
	
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
		/* Reset RTC Counter when Time is 23:59:59 */
		if (RTC_GetCounter() == 0x00015180)
		{
			RTC_SetCounter(0x0);
			/* Wait until last write operation on RTC registers has finished */
			RTC_WaitForLastTask();
		}
	}
}

static u8 led_flag=0;
extern u8 bug_flag;

u16 Temp_table[160]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//ÿ���Ӽ�¼���¶�����

void TIM4_IRQHandler(void)
{	
		u16 i=0;
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);	/* �������жϱ�־ */
		Time_Show();//ˢ��ʱ��
		display_2();//��ʾʱ��
		
		led_flag=!led_flag;
		PCout(0)=led_flag;
	//	IWDG_Feed();
		if(bug_flag == 0)
		{
					bug_flag=1;
					for(i=0;i<360;i++)
					{
							POINT_COLOR=WHITE;//���ʵ��ڰ�ɫ�������ϴλ�����
							LCD_DrawLine(120,100,Lcd_TimeX(120,60-10,i*6),Lcd_TimeY(100,60-10,i*6));
					}
		}
}


/*
void EXTI3_IRQHandler(void)
{	 
   u8 time=0,ok=0,data=0,err=0;
   
   while(1)
   {
	   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 1)
	   {
					time=hy_jssj();//��ô˴θߵ�ƽʱ��

					if(time>=250)  break;//������Ч�ź�
				
					if(time>=200 && time<250)
					{						 
						ok=1;//�յ������ź�	
					}
					else if(time>=60 && time<90)//1.2-1.8
					{
							data=1;//�յ�����1 
						
					}
					else if(time>=10 && time<50)//0.2-1.0
					{
							data=0;//�յ�����0
					}
					
					if(ok == 1)
					{
							hw_data<<=1;
							hw_data+=data;
							
							if(err>=32)
							{
								flag_hw_data=1;	
								break;		
							}		
					} 
			err++;
			}
   }  
   EXTI_ClearITPendingBit(EXTI_Line3);//���
}
*/

static u8 bTemp,bTemp_flag;		//��ʱ��������
u8 Re_buf[11];								//��������
u8 counter=0;									//���������±�
u8 sign=0;										//������ɱ�־λ
extern u8 KeyFuncIndex; 

void USART1_IRQHandler(void)
{
		
		/* ���ڽ��� */
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
		{
				/* �崮���жϱ�� */
				bTemp = USART_ReceiveData(USART1);
				
				LCD_ShowxNum(24*4,24*9,bTemp,4,24,0);
			
				/*�ж��ǲ���֡ͷ  0x80*/
				if(counter == 0)
				{
						if(bTemp == 0xef)
						{
								bTemp_flag = 1;									//�������ݱ�־λ
						}
						else 
						{
								printf("֡ͷ����\n");
								counter = 0;								//�����������λ��
								bTemp_flag = 0;									//����������ݱ�־λ
								return;
						}	
				}
				
				/*��ʼ���ݽ���*/
				if(bTemp_flag == 1)
				{
						if(bTemp == 0xef)							//����ڽ������ݵ�ʱ������֡ͷ����ô���¼���
						{
								counter = 0;
						}
						
						Re_buf[counter] = bTemp;					//�������ݱ���
						printf("֡ͷ��ȷ:%d  0x%x\n",counter,bTemp);
						counter++;											
										
						if(counter == 11)		//���ݽ�������ж�֡β
						{
								if((Re_buf[counter-1] == 0xfe) && (Re_buf[1] == 0x51 || Re_buf[1] == 0x52 || Re_buf[1] == 0x53))
								{
										sign = 1;
								}
								else
								{
										printf("���ݴ���\n");
								}
								counter = 0;								//�����������λ��
								bTemp_flag = 0;									//����������ݱ�־λ
						}	
				}	
		}
//		USART1->SR = 0;
 		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
