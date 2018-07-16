#ifndef _modbus_h_
#define _modbus_h_

#include "XC_Config.h"

#define b485Send1 PAout(1)
#define b485Send2 PCout(9)

void InitProg_485(void);
void TimeProc(void);
void checkComm0Modbus(void);

void GetDataFromSensor(unsigned char ucData);

void UpLoadData(void);

#endif
