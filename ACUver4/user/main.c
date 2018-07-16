/**
  ******************************************************************************
  * @file    main.c
  * @author  XC_
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台: STM32 开发板 
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
//#define flash_adr 0x0807f800	//定义主存储器的保存数据的起始地址0x0807F800
u32 flash_data=0;


unsigned int Display_LED=0;
void FLASHINIT_FLASH()
{	
	FLASH_Unlock();//解锁	
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
	FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位	
	FLASH_ErasePage(flash_adr);//要擦出页的起始地址	
	FLASH_ProgramHalfWord(flash_adr,flash_data);//写数据
	//FLASH_ProgramWord(FLASH_ADR+4,data);//接着上面写内容给flash，每写一次是一个字即四个字节	
	FLASH_Lock();//锁定
	flash_data=0;
	flash_data=(*(u16*)(flash_adr));	//__IO uint32_t
	
}
/**
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：无调用
 * 作者  :YaoTong 2017
 */



void ACU_Init(void)
{
	Device_RWReg_Union.device.Address_ACU = 255;
	Device_RWReg_Union.device.Address_ExternRS485  = 0;
	Device_RWReg_Union.device.SensorTotalNum = 0;
	Device_RWReg_Union.device.WorkMod = 0;
	Device_RWReg_Union.device.UploadPeriod = 500;
	Device_RWReg_Union.device.RS485_Sensor_Baud = 0; //0代表9600，6代表115200
	
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
	  Delay_Init(72);         	    /*初始化 延时*/
    InitProg_485();						/*MODBUS 485初始化*/		
		Input_Init();
		LED_HC595_Init();
		//看门狗
		IWDG_Init(0,200);    //与分频数为4,重载值为100,溢出时间为20ms	

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
			//PC与ACU的modbus通信
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
			//ACU读取下挂传感器数据
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
				//先判断上一个访问的传感器是否离线
				/*
				if(LiXian_flag[sensorNum_nowAccess]==1)
				{
				//离线
					//setRegisterVal(sensorNum_nowAccess*Device_RWReg_Union.device.BytesPerSensor + i,0xFFFE);
					//需要修改
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
				//轮流发出访问传感器命令
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
			
			//主动上传模式下，向PC周期性发送数据
			
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

