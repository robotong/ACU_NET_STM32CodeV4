#ifndef _RELAY_H
#define _RELAY_H

#include "MyMap.h"
#include "stdint.h"

void RelayInit(void);

void Relay0_ON(void);
void Relay0_OFF(void);
void Relay1_ON(void);
void Relay1_OFF(void);
void Relay2_ON(void);
void Relay2_OFF(void);
void Relay3_ON(void);
void Relay3_OFF(void);
void Relay4_ON(void);
void Relay4_OFF(void);
void Relay5_ON(void);
void Relay5_OFF(void);
void Relay6_ON(void);
void Relay6_OFF(void);
void Relay7_ON(void);
void Relay7_OFF(void);

extern void RelayAndLedUpdate(DeviceRegister__TypeDef *device_acu);
extern void AllRelayControl(DeviceRegister__TypeDef *device_acu);

#endif

