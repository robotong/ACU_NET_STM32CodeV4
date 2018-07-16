#ifndef _RESISTER_h_
#define _RESISTER_h_

#include "XC_Config.h"
#include "MyMap.h"

/*
	01���ܽ���03  02���ܽ���04  05���ܽ���06  15���ܽ���16 
	����������ɢ������ 02 04��������ֻ�� ��ɢ����������Ϊ������λ�������
*/

/*************************��ɢ����źţ��ɶ���д��Ȧ���ɿ��ƹ����� 01 05 15****************************************/
#define RWSTATUES0                 		 0    
#define RWSTATUES1                		 1
#define RWSTATUES2                 		 2    
#define RWSTATUES3                		 3  
#define RWSTATUES4                 		 4    
#define RWSTATUES5                		 5  
#define RWSTATUES6                 		 6    
#define RWSTATUES7                		 7  
    
/*************************��ɢ�����źţ�ֻ����Ȧ���ɿ��ƹ����� 02****************************************/
#define ROSTATUES0                      10000   
#define ROSTATUES1                      10001    
#define ROSTATUES2                      10002   
#define ROSTATUES3                      10003
#define ROSTATUES4                      10004   
#define ROSTATUES5                      10005
#define ROSTATUES6                      10006   
#define ROSTATUES7                      10007

/*************************����Ĵ�����ֻ�ܶ��Ĵ������ɿ��ƹ����� 04***********************************/
#define RODAT0                          30000     
#define RODAT1                          30001    
#define RODAT2                          30002
#define RODAT3                          30003         
#define RODAT4                          30004     
#define RODAT5                          30005    
#define RODAT6                          30006
#define RODAT7                          30007
  
#define TEMP0                           30008   	  //������ռ�����ֽ� 
#define TEMP1                           30010
#define TEMP2                           30012
#define TEMP3                           30014
#define TEMP4                           30016
#define TEMP5                           30018
#define TEMP6                           30020
#define TEMP7                           30022

/*************************���ּĴ���(�ɶ���д�Ĵ���)�ɿ��ƹ����� 03 06 16******************************/
#define RWDAT0                          40000        
#define RWDAT1                          40001       
#define RWDAT2                          40002 
#define RWDAT3                          40003 
#define RWDAT4                          40004        
#define RWDAT5                          40005       
#define RWDAT6                          40006 
#define RWDAT7                          40007

#define ADC00                           40008         //long��ռ�����ֽ�     
#define ADC11                           40010
#define ADC22                           40012
#define ADC33                           40014
#define ADC44                           40016
#define ADC55                           40018
#define ADC66                           40020
#define ADC77                           40022   

#define ResisterAddressMax              1085


#define index_ACUAddress                1024
#define index_SensorTotalNum            1025

#define AddressOffset_DataOfPerSensor          0
#define AddressOffset_NumOfPerSensor           1024
//�������üĴ����׵�ַ
#define AddressOffset_Setting                  1280

extern u16   RWReg[1290];
extern u8    Relay_State;
extern u16 	 InputData;
extern u8 SensorLeaveFlag;
extern u8 System_State;

extern DeviceRegister__TypeDef Device_RWReg_Union;

uint16_t RegisterMap_ReadData(uint16_t index);
void RegisterMap_WriteData(uint16_t index, uint16_t data);

u16 getCoilVal(u16 addr,u16 *tempData);
u16 setCoilVal(u16 addr,u16 tempData);
u16 getRegisterVal(u16 addr,u16 *tempData);
u16 setRegisterVal(u16 addr,u16 tempData);
void RelayCtl(void);
  

#endif









    














