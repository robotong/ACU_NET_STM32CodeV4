#ifndef __USART_H
#define	__USART_H
#include "XC_Config.h"
#include "stdio.h"


void USART1_Config(unsigned long baudrate);			//���ڴ���USART1������
int fputc(int ch, FILE *f);			//��Ҫʹ��printf()��������printf()���¶��򵽴�����
void USART1_printf(USART_TypeDef *USARTx, uint8_t *Data,...);  //��ʽ�������������C���е�printf��������û���õ�C��
void USART1_Putc(unsigned char c);//����һ����һ�ַ�
void USART1_Puts(char *str);//����һ����һ�ַ���
void USART_Delivery(u32 date,u8 USART_Delivery_flag);//�򴮿ڷ�������
void USART2_Config(unsigned long baudrate);
void UART4_Config(unsigned long baudrate);

#endif /* __USART1_H */	
