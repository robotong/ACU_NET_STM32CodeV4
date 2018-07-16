#include "delay.h"


static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

void Delay_Init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}


//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}


//延时us								   
void delay_us(u32 Nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=Nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	    
} 


 /**
 * 函数名：TIM2_Configuration
 * 描述  ：初始化函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	
    TIM_DeInit(TIM2);
	  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_TimeBaseStructure.TIM_Period=10-1; 				    /* 自动重装载寄存器周期的值(计数值) */

    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= 7199;				            /* 时钟预分频数 72M */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	     	/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);							/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);											/* 开启时钟 */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);		    
}

