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
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//每分钟记录下温度数据

void TIM4_IRQHandler(void)
{	
		u16 i=0;
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);	/* 清除溢出中断标志 */
		Time_Show();//刷新时间
		display_2();//显示时间
		
		led_flag=!led_flag;
		PCout(0)=led_flag;
	//	IWDG_Feed();
		if(bug_flag == 0)
		{
					bug_flag=1;
					for(i=0;i<360;i++)
					{
							POINT_COLOR=WHITE;//画笔等于白色，消隐上次画的线
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
					time=hy_jssj();//获得此次高电平时间

					if(time>=250)  break;//不是有效信号
				
					if(time>=200 && time<250)
					{						 
						ok=1;//收到起诉信号	
					}
					else if(time>=60 && time<90)//1.2-1.8
					{
							data=1;//收到数据1 
						
					}
					else if(time>=10 && time<50)//0.2-1.0
					{
							data=0;//收到数据0
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
   EXTI_ClearITPendingBit(EXTI_Line3);//清除
}
*/

static u8 bTemp,bTemp_flag;		//临时接收数据
u8 Re_buf[11];								//接收数组
u8 counter=0;									//接收数组下标
u8 sign=0;										//接收完成标志位
extern u8 KeyFuncIndex; 

void USART1_IRQHandler(void)
{
		
		/* 串口接收 */
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
		{
				/* 清串口中断标记 */
				bTemp = USART_ReceiveData(USART1);
				
				LCD_ShowxNum(24*4,24*9,bTemp,4,24,0);
			
				/*判断是不是帧头  0x80*/
				if(counter == 0)
				{
						if(bTemp == 0xef)
						{
								bTemp_flag = 1;									//接收数据标志位
						}
						else 
						{
								printf("帧头错误\n");
								counter = 0;								//清除接收数据位数
								bTemp_flag = 0;									//清除接收数据标志位
								return;
						}	
				}
				
				/*开始数据接收*/
				if(bTemp_flag == 1)
				{
						if(bTemp == 0xef)							//如果在接收数据的时候发现了帧头，那么重新计算
						{
								counter = 0;
						}
						
						Re_buf[counter] = bTemp;					//接收数据保持
						printf("帧头正确:%d  0x%x\n",counter,bTemp);
						counter++;											
										
						if(counter == 11)		//数据接收完毕判断帧尾
						{
								if((Re_buf[counter-1] == 0xfe) && (Re_buf[1] == 0x51 || Re_buf[1] == 0x52 || Re_buf[1] == 0x53))
								{
										sign = 1;
								}
								else
								{
										printf("数据错误\n");
								}
								counter = 0;								//清除接收数据位数
								bTemp_flag = 0;									//清除接收数据标志位
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
