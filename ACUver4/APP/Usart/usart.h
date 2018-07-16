#ifndef __USART_H
#define	__USART_H
#include "XC_Config.h"
#include "stdio.h"


void USART1_Config(unsigned long baudrate);			//关于串口USART1的配置
int fputc(int ch, FILE *f);			//想要使用printf()函数，把printf()重新定向到串口中
void USART1_printf(USART_TypeDef *USARTx, uint8_t *Data,...);  //格式化输出，类似于C库中的printf，但这里没有用到C库
void USART1_Putc(unsigned char c);//串口一发送一字符
void USART1_Puts(char *str);//串口一发送一字符串
void USART_Delivery(u32 date,u8 USART_Delivery_flag);//向串口发送数据
void USART2_Config(unsigned long baudrate);
void UART4_Config(unsigned long baudrate);

#endif /* __USART1_H */	
