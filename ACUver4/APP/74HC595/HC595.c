
#include "DIO.h"
#include "HC595.h"

unsigned char LED_array[28] = {0};

#define SDATA_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define SDATA_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define SCLK_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define SCLK_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define RCK_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define RCK_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_6)
#define OE_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_5)
#define OE_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_5)


#define uint unsigned int
#define uchar unsigned char

//继电器控制初始化
void HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 

	OE_595_Reset;	

}

void WR_595_8bits(uchar temp)
{
     uchar j;
      for (j=0;j<8;j++)
     {
      
			 if(temp&0x0001)
			 {
				 SDATA_595_Set;
			 }else
       {
				 SDATA_595_Reset;
			 }
      SCLK_595_Set;                    
       __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
      SCLK_595_Reset;
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
			temp=temp>>1 ;
     }     
		RCK_595_Reset;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
    RCK_595_Set; 
}

void WR_595_16bits(uint temp)
{
     uchar j;
      for (j=0;j<16;j++)
     {
      
			 if(temp&0x0001)
			 {
				 SDATA_595_Set;
			 }else
       {
				 SDATA_595_Reset;
			 }
      SCLK_595_Set;                    
       __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
      SCLK_595_Reset;
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
			temp=temp>>1 ;
     }     
		RCK_595_Reset;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
    RCK_595_Set; 
}


#define LED_SDATA_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define LED_SDATA_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_0)
#define LED_SCLK_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_3)
#define LED_SCLK_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_3)
#define LED_RCK_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_2)
#define LED_RCK_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_2)
#define LED_OE_595_Set GPIO_SetBits(GPIOC, GPIO_Pin_1)
#define LED_OE_595_Reset GPIO_ResetBits(GPIOC, GPIO_Pin_1)

void LED_HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 

	LED_OE_595_Reset;	
	
	//LED_WR_595_28bits(LED_array);

}

void LED_WR_595_8bits(uchar temp)
{
     uchar j;
      for (j=0;j<8;j++)
     {
      
			 if(temp&0x0001)
			 {
				 LED_SDATA_595_Set;
			 }else
       {
				 LED_SDATA_595_Reset;
			 }
      LED_SCLK_595_Reset;                    
       __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
      LED_SCLK_595_Set;
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
			temp=temp>>1 ;
     }     
		LED_RCK_595_Reset;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
    LED_RCK_595_Set; 
}

void LED_WR_595_28bits(uchar temp[])
{
     uchar j;
      for (j=0;j<28;j++)
     {
      
			 if(temp[27-j]&0x0001)
			 {
				 LED_SDATA_595_Reset;
			 }else
       {
				 LED_SDATA_595_Set;
			 }
      LED_SCLK_595_Set;                    
       __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
      LED_SCLK_595_Reset;
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
			//temp=temp>>1 ;
     }     
		LED_RCK_595_Reset;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
    LED_RCK_595_Set; 
}

void LED_WR_595_28bits_YAO(unsigned int temp)
{
     uchar j;
      for (j=0;j<28;j++)
     {
      
			 if(temp&0x00000001)
			 {
				 LED_SDATA_595_Reset;
			 }else
       {
				 LED_SDATA_595_Set;
			 }
      LED_SCLK_595_Set;                    
       __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
      LED_SCLK_595_Reset;
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
       __nop();
			temp=temp>>1 ;
     }     
		LED_RCK_595_Reset;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
    LED_RCK_595_Set; 
}

