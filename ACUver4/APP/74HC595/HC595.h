#ifndef _HC595_H
#define _HC595_H

extern unsigned char LED_array[28];

void HC595_Init(void);
void WR_595_8bits(unsigned char temp);
void WR_595_16bits(unsigned int temp);

void LED_HC595_Init(void);
void LED_WR_595_8bits(unsigned char temp);
void LED_WR_595_28bits(unsigned char temp[]);
void LED_WR_595_28bits_YAO(unsigned int temp);


#endif
