/**
  ******************************************************************************
  * @file    main.c
  * @author  XC_
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨: STM32 ������ 
  * B5
  ******************************************************************************
  */
#include "XC_Config.h"
//#include "math.h"
#include "HC595.h"
#include "DIO.h"
#include "stm32f10x_flash.h"
#include "flash.h"
#include "RESISTER.h"
#include "relay.h"
#include "wdg.h"





extern void uart2sends(u8 buff[],u8 len);

unsigned char LiXian_flag[256];

extern u8 SendCMD03toSensor(u8 addr,u16 registerStartaddr,u16 registernum);
extern  u8    RWstatus0;

extern u8 sensorNum_nowAccess;

u16   timeMs; 
u16   timeMs_Uoload;

#define flash_adr 0x0800FC00
//#define flash_adr 0x0807f800	//�������洢���ı������ݵ���ʼ��ַ0x0807F800
u32 flash_data=0;


unsigned int Display_LED=0;
void FLASHINIT_FLASH()
{	
	FLASH_Unlock();//����	
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
	FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//�����־λ	
	FLASH_ErasePage(flash_adr);//Ҫ����ҳ����ʼ��ַ	
	FLASH_ProgramHalfWord(flash_adr,flash_data);//д����
	//FLASH_ProgramWord(FLASH_ADR+4,data);//��������д���ݸ�flash��ÿдһ����һ���ּ��ĸ��ֽ�	
	FLASH_Lock();//����
	flash_data=0;
	flash_data=(*(u16*)(flash_adr));	//__IO uint32_t
	
}
/**
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 * ����  ���޵���
 * ����  :YaoTong 2017
 */



void ACU_Init(void)
{
	Device_RWReg_Union.device.Address_ACU = 255;
	Device_RWReg_Union.device.Address_ExternRS485  = 0;
	Device_RWReg_Union.device.SensorTotalNum = 0;
	Device_RWReg_Union.device.WorkMod = 0;
	Device_RWReg_Union.device.UploadPeriod = 500;
	Device_RWReg_Union.device.RS485_Sensor_Baud = 0; //0����9600��6����115200
	
	Device_RWReg_Union.device.RS485_Extend_Baud = 0;
	Device_RWReg_Union.device.RS485_4G_Baud = 0;
	Device_RWReg_Union.device.ACU_State = 0;
	Device_RWReg_Union.device.AllRelay_State = 0;
	Device_RWReg_Union.device.Input_State = 0;
	Device_RWReg_Union.device.RJ45Busy = 0;
	Device_RWReg_Union.device.SensorTotalNum = 0;	
}

int main(void)
{	  
		
		u8  i=0;
	
		ACU_Init();
		ReadDataFromFlash(64,160,8);
		RelayInit();
		//FLASHINIT_FLASH();
		NVIC_Configuration();   	    /*Priority configuration*/
	  Delay_Init(72);         	    /*��ʼ�� ��ʱ*/
    InitProg_485();						/*MODBUS 485��ʼ��*/		
		Input_Init();
		LED_HC595_Init();
		//���Ź�
		IWDG_Init(0,200);    //���Ƶ��Ϊ4,����ֵΪ100,���ʱ��Ϊ20ms	

		while(1)
		{ 
				
	//			uart2sends("abcd",4);
	//			uart1sends("abcd",4);
	//		  uart4sends("abcd",4);
		 //delay_ms(1000);
			
			//StateDisplay();
			InputData=GetInputData();
			Device_RWReg_Union.device.Input_State = GetInputData();
			SystemStateDisplay(&Device_RWReg_Union);
			//PC��ACU��modbusͨ��
			checkComm0Modbus();
			//RelayCtl();
			AllRelayControl(&Device_RWReg_Union);
			RelayAndLedUpdate(&Device_RWReg_Union);

			//b485Send2  = 1;
			//USART_SendData(UART4,22);
			//delay_ms(10);
			//b485Send2  = 0;
			//delay_ms(1000);
			//LED_WR_595_28bits_YAO(Display_LED);
			//ACU��ȡ�¹Ҵ���������
			if(Device_RWReg_Union.device.SensorTotalNum == 0)
			{
				sensorNum_nowAccess = 0;
				SensorLeaveFlag = 0;	
				timeMs = 0;	
				i	= 0;			
			}
			else if(timeMs>250)
			{
				timeMs=0;
				//���ж���һ�����ʵĴ������Ƿ�����
				/*
				if(LiXian_flag[sensorNum_nowAccess]==1)
				{
				//����
					//setRegisterVal(sensorNum_nowAccess*Device_RWReg_Union.device.BytesPerSensor + i,0xFFFE);
					//��Ҫ�޸�
					//setRegisterVal(sensorNum_nowAccess*Device_RWReg_Union.device.BytesPerSensor,0xFFFE);
					//Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data[0] = 0xFFFE;
					//Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data[1] = 0xFFFE;
					//Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data[2] = 0xFFFE;
					//Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data[3] = 0xFFFE;
					SensorLeaveFlag=1;
				}else
				{
					SensorLeaveFlag=0;
				}				
				*/
				//�����������ʴ���������
				if(i<Device_RWReg_Union.device.SensorTotalNum)
				{
					sensorNum_nowAccess=i;				
					SendCMD03toSensor(Device_RWReg_Union.device.sensor[sensorNum_nowAccess].sensor_address,Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data_firstaddress,Device_RWReg_Union.device.sensor[sensorNum_nowAccess].data_quantity);
					LiXian_flag[i]=1;
				}
				i++;
				if(i>=Device_RWReg_Union.device.SensorTotalNum)
				{
					i=0;
				}
			}
			
			//�����ϴ�ģʽ�£���PC�����Է�������
			
			if(Device_RWReg_Union.device.WorkMod==1)
			{
				if(timeMs_Uoload>Device_RWReg_Union.device.UploadPeriod)
				{
					
					timeMs_Uoload=0;
					UpLoadData();
				}
			}
			
		}	
}

