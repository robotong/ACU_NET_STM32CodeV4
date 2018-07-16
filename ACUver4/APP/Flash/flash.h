#ifndef _flash_H
#define _flash_H
#include "stm32f10x.h"


void WriteDataToFlash(uint16_t relaySetNum, uint16_t sensorSetNum, uint16_t systemSetNum);
void ReadDataFromFlash(uint16_t relaySetNum, uint16_t sensorSetNum, uint16_t systemSetNum);



#endif
