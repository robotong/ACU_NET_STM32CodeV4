#include "stm32f10x_flash.h"
#include "flash.h"
#include "MyMap.h"
#include "RESISTER.h"


#define flashPage_adr 0x0800FC00
void WriteDataToFlash(uint16_t relaySetNum, uint16_t sensorSetNum, uint16_t systemSetNum)
{
  uint16_t i;
	
	
	FLASH_Unlock();//解锁	
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位	
	FLASH_ErasePage(flashPage_adr);//要擦出页的起始地址	
	
	//存储设置变量
	for(i=0; i < (relaySetNum + sensorSetNum + systemSetNum); i++)
	{
		if(i<relaySetNum)
		{
			FLASH_ProgramHalfWord(flashPage_adr+i*2,RegisterMap_ReadData(i+41000));//写数据
		}
		else if(i<(relaySetNum + sensorSetNum))   //(64+160)
		{
			FLASH_ProgramHalfWord(flashPage_adr + i*2,RegisterMap_ReadData(i-relaySetNum+42000));//写数据
		}
		else if(i<(relaySetNum + sensorSetNum + systemSetNum))   //(56+160+8)
		{
			FLASH_ProgramHalfWord(flashPage_adr+i*2,RegisterMap_ReadData(i-(relaySetNum + sensorSetNum)+44000));//写数据
		}
	}
	FLASH_Lock();//锁定
}

void ReadDataFromFlash(uint16_t relaySetNum, uint16_t sensorSetNum, uint16_t systemSetNum)
{
  uint16_t i;
	//uint16_t temp;
	for(i=0;i<(relaySetNum + sensorSetNum + systemSetNum);i++)
	{	
		//*pData=(*(u16*)(flashPage_adr+i*2));	//__IO uint32_t
		
		if((*(u16*)(flashPage_adr+i*2)) == 0xffff)
		{
			FLASH_Unlock();//解锁	
			FLASH_ProgramHalfWord(flashPage_adr+i*2,0);//写数据
			FLASH_Lock();//锁定
		}
		
		if(i<relaySetNum)
		{
			RegisterMap_WriteData(i+41000,(*(u16*)(flashPage_adr+i*2)));//读数据
		}
		else if(i<(relaySetNum+sensorSetNum))   //(64+160)
		{
			RegisterMap_WriteData(i+42000-relaySetNum,(*(u16*)(flashPage_adr+i*2)));//读数据
		}
		else if(i<(relaySetNum + sensorSetNum + systemSetNum))   //(56+160+8)
		{
			RegisterMap_WriteData(i+44000-(relaySetNum + sensorSetNum),(*(u16*)(flashPage_adr+i*2)));//读数据
		}
	}


}


