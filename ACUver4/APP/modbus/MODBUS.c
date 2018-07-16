#include "MODBUS.h"
#include "RESISTER.h"
#include "MODBUS_CRC.h"
#include "flash.h"
u16 b=0;
u16 test2=0;
u16 test3=0;
u8 test=0;
	u8 LocalAddr = 0x01; 								   //�ӻ���ַ��Ĭ��Ϊ0X01

	u8   receTimeOut_USART1;            	     		 //���ճ�ʱ
	u8   sendCount;  			 		 						 //���ͳ�ȥ�ֽڸ���
	u8   receCount_USART1;    		  			 				 //���յ����ֽڸ���
	u8   receBuf_USART1[50];
	u8   sendBuf_USART1[50];
	
	u8   receBuf_USART4[50];
	u8   sendBuf_USART4[50];
	u8   receCount_USART4; 
	
	
	
	u8   sendPosi;	    			     				 //����λ��

	u8   sendBuf_Upload[280];
	u8   sendCount_Upload;

uint32_t BAUDtable[] = {9600,14400,19200,38400,56000,57600,115200};

 /**
 * ��������InitProg_485
 * ����  ����ʼ������
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void InitProg_485(void)
{        	
	
	GPIO_InitTypeDef  GPIO_InitStructure;					
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*
		485�շ���������
    �͵�ƽ����ģʽ
    �ߵ�ƽ����ģʽ
  */
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//	GPIO_SetBits(GPIOC,GPIO_Pin_9);
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	
	USART1_Config(115200);     		//����1 ��ʼ��  ������9600  ��У��
	USART2_Config(BAUDtable[Device_RWReg_Union.device.RS485_Sensor_Baud]); //��ȡ��������
	UART4_Config(BAUDtable[Device_RWReg_Union.device.RS485_Extend_Baud]); //���������豸
//		USART2_Config(9600); 
//	UART4_Config(9600); 
	TIM2_Configuration();		//��ʼ����ʱ��2  1MS
	//Address_ACU = Addr;       //���ôӻ���ַ
} 

/**
 * ��������uart1sends
 * ����  �����ͺ���,�����ڷ���
 * ����  ��buff ����  len ����
 * ���  ����
 * ����  ���ڲ�����
 * ����  :YaoTong 2017
 */
void uart1sends(u8 buff[],u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1,buff[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
}

/**
 * ��������uart1sends
 * ����  �����ͺ���,����չ��RS485��������
 * ����  ��buff ����  len ����
 * ���  ����
 * ����  ���ڲ�����
 * ����  :YaoTong 2017
 */
void uart4sends(u8 buff[],u8 len)
{
    u8 i;
    for(i=0; i<len; i++)
    {
        USART_SendData(UART4,buff[i]);
        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    }
}

/*
//�������ݵ���չRS485�ӿ�
void SendDataToExternRS485(void)
{
  //ֻҪ��ַƥ�䣬�����߽��յ�ʲþʹ����ʲô��չRS485�ӿ�
	uart4sends(receBuf_USART1,8);
}
*/


/**
 * ��������Begin_send
 * ����  �����ڷ��ͺ���
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void Begin_send(void)
{
//	b485Send = 1;      				//���ڷ���
	uart1sends(sendBuf_USART1,sendCount);
//	b485Send = 0;   	    		//�������485���ڽ���״̬
  receCount_USART1 = 0;          	//����յ�ַƫ�ƼĴ���
}


/**
 * ��������readCoils
 * ����  ��������������Ȧ״̬  fuction:01
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void readCoils(void)
{
	u16 addr;
	u16 tempAddr;
	u16 byteCount;
	u16 bitCount;
	u16 crcData;
	u16 position;
	u16 i,k;
	u16 tempData;
	u8 exit = 0;
	
	test=1;
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3]; 
	tempAddr = addr;
	bitCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; //��ȡ��λ����
	byteCount = bitCount / 8;    			 //�ֽڸ���
	if(bitCount%8 != 0)
	byteCount++;       
	for(k=0;k<byteCount;k++)				 //�ֽ�λ��
	{
		position = k + 3;
		sendBuf_USART1[position] = 0;
		for(i=0;i<8;i++)
		{
			getCoilVal(tempAddr,&tempData);
			
			sendBuf_USART1[position] |= tempData << i;
			tempAddr++;
			if(tempAddr >= (addr+bitCount))  //����
			{ 
				exit = 1;
				break;
			} 
		}
		if(exit == 1)
		break;
	}
	test=3;
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;                 //�豸��ַ
	sendBuf_USART1[1] = 1; 						//������ : 1
	sendBuf_USART1[2] = byteCount;       			//��Ȧ������Ӧ���ֽ���
	byteCount += 3;							
	crcData = crc16(sendBuf_USART1,byteCount);		//����CRCУ���� 
	sendBuf_USART1[byteCount] = crcData & 0xff;	//CRCУ�����λ��ǰ
	byteCount++;							
	sendBuf_USART1[byteCount] = crcData >> 8;		//CRCУ�����λ�ں�
	sendCount = byteCount + 1;				//���ͳ�ȥ���ݸ���
	Begin_send();   
}	

/**
 * ��������readInPutCoils
 * ����  ����ȡ��Ȧ���루ֻ���Ĵ�����״̬  fuction:02
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void readInPutCoils(void)
{
	u16 addr;
	u16 tempAddr;
	u16 byteCount;
	u16 bitCount;
	u16 crcData;
	u16 position;
	u16 i,k;
	u16 tempData;
	u8 exit = 0;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3];
	//ֻ����Ȧ�Ĵ���ƫ�Ƶ�ַROSTATUES0��10000��
	tempAddr = addr + ROSTATUES0;        			
	bitCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 	
	byteCount = bitCount / 8;    				
	if(bitCount%8 != 0)
	byteCount++;       
	for(k=0;k<byteCount;k++)					
	{
		position = k + 3;
		sendBuf_USART1[position] = 0;
		for(i=0;i<8;i++)
		{
			getCoilVal(tempAddr,&tempData);
			sendBuf_USART1[position] |= tempData << i;
			tempAddr++;
			//����,���ϼĴ�����ƫ�Ƶ�ַ
			if(tempAddr >= (addr + bitCount + ROSTATUES0))		
			{ 
				exit = 1;
				break;
			} 
		}
		if(exit == 1)
		break;
	}
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;						
	sendBuf_USART1[1] = 2;
	//��ɢ״̬������Ӧ���ֽ���	
	sendBuf_USART1[2] = byteCount;						
	byteCount += 3;
	crcData = crc16(sendBuf_USART1,byteCount); 		
	sendBuf_USART1[byteCount] = crcData & 0xff;        
	byteCount++;
	sendBuf_USART1[byteCount] = crcData >> 8;          
	sendCount = byteCount + 1;					
	Begin_send();   
}

/**
 * ��������readRegisters
 * ����  ����ȡ����Ĵ���ֵ  fuction:03
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void readRegisters(void)
{
	u16 addr;
	u16 tempAddr;
	u16 crcData;
	u16 readCount;
	u16 byteCount;
	u16 i;
	u16 tempData = 0; 
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3]; 
	tempAddr = addr + RWDAT0;      				//���ּĴ���ƫ�Ƶ�ַRWDAT0��40000��
	//tempAddr = addr;      				//���ּĴ��� u16   RWReg[1034];��ַ���㿪ʼ
	readCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 	//Ҫ���ĸ��� ,����
	byteCount = readCount * 2;                  //ÿ���Ĵ�������ռ�ߣ��������ֽ�
	test3 = tempAddr;
	for(i=0;i<byteCount;i+=2,tempAddr++)
	{
		//getRegisterVal(tempAddr,&tempData); 
		
		test2= RegisterMap_ReadData(41000);
		tempData = RegisterMap_ReadData(tempAddr);
		sendBuf_USART1[i+3] = tempData >> 8;        
		sendBuf_USART1[i+4] = tempData & 0xff;  
	}
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;						//�豸��ַ
	sendBuf_USART1[1] = 3;  							//������ : 03
	sendBuf_USART1[2] = byteCount;						//���ּĴ���������Ӧ���ֽ���
	byteCount += 3;             				//����ǰ��ĵ�ַ�������룬��ַ ��3+byteCount���ֽ�
	crcData = crc16(sendBuf_USART1,byteCount);			//����CRCУ����
	sendBuf_USART1[byteCount] = crcData & 0xff;   		//CRCУ�����λ��ǰ
	byteCount++;							    //CRCУ�����λ�ں�
	sendBuf_USART1[byteCount] = crcData >> 8 ;	   		//��λ�ں�
	sendCount = byteCount + 1;					//���ͳ�ȥ���ݸ���
	Begin_send();
}

/**
 * ��������readInPutRegisters
 * ����  ����ȡ����Ĵ���  fuction:04
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void readInPutRegisters(void)
{
	u16 addr;
	u16 tempAddr;
	u16 crcData;
	u16 readCount;
	u16 byteCount;
	u16 i;
	u16 tempData = 0; 
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3]; 
	tempAddr = addr + RODAT0;  					//����Ĵ���ƫ�Ƶ�ַRODAT0��30000��
	readCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 	//Ҫ���ĸ��� ,����
	byteCount = readCount * 2;                  //ÿ���Ĵ�������ռ�ߣ��������ֽ�
	
	for(i=0;i<byteCount;i+=2,tempAddr++)
	{
		getRegisterVal(tempAddr,&tempData);    
		sendBuf_USART1[i+3] = tempData >> 8;        
		sendBuf_USART1[i+4] = tempData & 0xff;  
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;					//�豸��ַ
	sendBuf_USART1[1] = 4;  						//������ : 04
	sendBuf_USART1[2] = byteCount;					//����Ĵ���������Ӧ���ֽ���
	byteCount += 3;             			//����ǰ��ĵ�ַ�������룬��ַ ��3+byteCount���ֽ�
	crcData = crc16(sendBuf_USART1,byteCount);		//����CRCУ����
	sendBuf_USART1[byteCount] = crcData & 0xff;   	//CRCУ�����λ��ǰ
	byteCount++;
	sendBuf_USART1[byteCount] = crcData >> 8 ;	   	//CRCУ�����λ�ں�
	sendCount = byteCount + 1;				//���ͳ�ȥ���ݸ���
	Begin_send();
}
	 
/**
 * ��������forceSingleCoil
 * ����  ��ǿ�Ƶ�����Ȧ  fuction:05
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void forceSingleCoil(void)
{
	u16 addr;
	u16 tempAddr;
	u16 tempData;
	u16  onOff;
	u8 i;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3]; 
	tempAddr = addr;
	onOff = (receBuf_USART1[4]<<8) + receBuf_USART1[5];
	
	/*��ΪON*/
	if(onOff == 0xff00)
	{ 
	    tempData = 1;
	} 
	/*��ΪOFF*/
	else if(onOff == 0x0000)
	{ 
	    tempData = 0;
	}
	setCoilVal(tempAddr,tempData); 
	for(i=0;i<receCount_USART1;i++)
	{
	    sendBuf_USART1[i] = receBuf_USART1[i];
	}
	sendCount = receCount_USART1;
	Begin_send(); 
}

/**
 * ��������presetSingleRegister
 * ����  �����õ����Ĵ���  fuction:06
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void presetSingleRegister(void)
{
	u16 addr;
	u16 tempAddr;
	u16 tempData;
	u16 crcData;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3];
	tempAddr = addr + RWDAT0;      				//���ּĴ���ƫ�Ƶ�ַRWDAT0��40000��
	//tempAddr = addr;      				//���ּĴ���ƫ�Ƶ�0
	b=tempAddr;
	tempData = (receBuf_USART1[4]<<8) + receBuf_USART1[5];
	b = tempData;
	RegisterMap_WriteData(tempAddr,tempData);
	//setRegisterVal(tempAddr,tempData); 
	//��Ϊ��������ʱ����flash�洢һ��
	if(addr>1023)
	{
		WriteDataToFlash(64,160,8);
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//�豸��ַ
	sendBuf_USART1[1] = 6;    				//������ : 06
	sendBuf_USART1[2] = addr >> 8;  		//�Ĵ�����ַ��λ
	sendBuf_USART1[3] = addr & 0xff;		//�Ĵ�����ַ��λ
	sendBuf_USART1[4] =receBuf_USART1[4];			//�Ĵ�����ֵ
	sendBuf_USART1[5] =receBuf_USART1[5];			//�Ĵ�����ֵ
	crcData = crc16(sendBuf_USART1,6);		//����CRCУ����
	sendBuf_USART1[6] = crcData & 0xff;  	//CRCУ�����λ��ǰ
	sendBuf_USART1[7] = crcData >> 8;	  	//CRCУ�����λ�ں�
	sendCount = 8;					////���ͳ�ȥ���ݸ���
	Begin_send(); 
}

/**
 * ��������forceMultipleCoils
 * ����  ��ǿ�ö���Ȧֵ  fuction:15
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void forceMultipleCoils(void)
{
	u16 addr;
	u16 tempAddr;
	u16 byteCount;
	u16 bitCount;
	u16 crcData;
	u16 tempData;
	u16 i,k;
	u8 exit = 0;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3];
	tempAddr = addr;
	
	bitCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5];
	byteCount = bitCount / 8;    //�ֽڸ���
	if(bitCount%8 != 0)
	byteCount++;
	
	for(k=0;k<byteCount;k++)    //�ֽ�λ��
	{
			for(i=0;i<8;i++)
			{
					tempData = (receBuf_USART1[k+7] >> i)&0x01;  
					setCoilVal(tempAddr,tempData); 
					tempAddr++;
					if(tempAddr >= (addr + bitCount + 8))//����
					{ 
						exit = 1;
						break;
					} 
			}
			if(exit == 1)
			break;
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//�豸��ַ
	sendBuf_USART1[1] = 15;    			//������ : 15
	sendBuf_USART1[2] = addr >> 8;  		//�Ĵ�����ַ��λ
	sendBuf_USART1[3] = addr & 0xff;		//�Ĵ�����ַ��λ
	sendBuf_USART1[4] = bitCount >> 8;		//�����üĴ���������λ
	sendBuf_USART1[5] = bitCount & 0xff;	//�����üĴ���������λ
	crcData = crc16(sendBuf_USART1,6);		//����CRCУ����
	sendBuf_USART1[6] = crcData & 0xff;  	//CRCУ�����λ��ǰ
	sendBuf_USART1[7] = crcData >> 8;	  	//CRCУ�����λ�ں�
	sendCount = 8;					//���ͳ�ȥ���ݸ���
	Begin_send(); 
}

/**
 * ��������presetMultipleRegisters
 * ����  �����ö���Ĵ���ֵ  fuction:16
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void presetMultipleRegisters(void)
{
	u16 addr;
	u16 tempAddr;
	u16 setCount;
	u16 crcData;
	u16 tempData;
	u8 i;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3];
	tempAddr = addr + RWDAT0;      				//���ּĴ���ƫ�Ƶ�ַRWDAT0��40000��
	//tempAddr = addr;
	setCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 
	for(i=0;i<setCount;i++,tempAddr++)
	{
		tempData = (receBuf_USART1[i*2+7]<<8) + receBuf_USART1[i*2+8];//�����üĴ���ֵ
		//setRegisterVal(tempAddr,tempData);  
		RegisterMap_WriteData(tempAddr,tempData);
	}
	//��Ϊ��������ʱ����flash�洢һ��
	if(addr>1023)
	{
		WriteDataToFlash(64,160,8);
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//�豸��ַ
	sendBuf_USART1[1] = 16;    			//������ : 16
	sendBuf_USART1[2] = addr >> 8;  		//�Ĵ�����ַ��λ
	sendBuf_USART1[3] = addr & 0xff;		//�Ĵ�����ַ��λ
	sendBuf_USART1[4] = setCount >> 8;		//�����üĴ���������λ
	sendBuf_USART1[5] = setCount & 0xff;	//�����üĴ���������λ
	crcData = crc16(sendBuf_USART1,6);		//����CRCУ����
	sendBuf_USART1[6] = crcData & 0xff;  	//CRCУ�����λ��ǰ
	sendBuf_USART1[7] = crcData >> 8;	  	//CRCУ�����λ�ں�
	sendCount = 8;					//���ͳ�ȥ���ݸ���
	Begin_send(); 
}


/**
 * ��������checkComm0Modbus
 * ����  ����ѯuart���յ����ݰ����ݺ���
 *         �Ի����ݴ��ڽ��յ������ݰ�receBuf_USART1[1]��������ݣ�
 *         ��function codeִ����Ӧ������
 *         10ms�ڱ�����Ӧ��������
 * ����  ��
 * ���  ��
 * ����  ���ⲿ����
 * ����  :YaoTong 2017
 */
void checkComm0Modbus(void)		   
{
	u16 crcData;
	u16 tempData;
	u16 temp;
	
	if(receCount_USART1 > 4)		 //������յ����ݸ�������4��
	{	 
		switch(receBuf_USART1[1])
		{
			case 0xff:
			{	 
				if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
				{   	
					if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)
					{	 
						crcData = crc16(receBuf_USART1,6);
						temp=receBuf_USART1[7];
						temp=(temp<<8) + receBuf_USART1[6];
						if(crcData == temp)
						if(receBuf_USART1[1] == 0X01)
						{ 
							readCoils();
						}
						receCount_USART1 = 0; 
					}	
				}      
				break;
			}
			case 1:
			{	 
				if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
				{   	
					if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)
					{	 
						crcData = crc16(receBuf_USART1,6);
						temp=receBuf_USART1[7];
						temp=(temp<<8) + receBuf_USART1[6];
						if(crcData == temp)
						if(receBuf_USART1[1] == 0X01)
						{ 
							readCoils();
						}
						receCount_USART1 = 0; 
					}	

				}      
				break;
			}
			case 2:
			{	 
				if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
				{   	 
					if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU) 
					{	 
						crcData = crc16(receBuf_USART1,6);
						temp=receBuf_USART1[7];
						temp=(temp<<8) + receBuf_USART1[6];
						if(crcData == temp)
						if(receBuf_USART1[1] == 0X02)
						{ 
							readInPutCoils(); 
						}
						receCount_USART1 = 0;
					}	
				}      
				break;
			}   
		case 3:
		{	 
			if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
			{   	 
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)  
				{	 
					crcData = crc16(receBuf_USART1,6);
					temp=receBuf_USART1[7];
					temp=(temp<<8) + receBuf_USART1[6];
					if(crcData == temp)
					if(receBuf_USART1[1] == 0X03)
					{ 
						readRegisters();
					}
					receCount_USART1 = 0;
				}		  
			}      
			break;
		}
		case 4:
		{	 
			if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
			{   	 
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)   
				{	 
					crcData = crc16(receBuf_USART1,6);
					temp=receBuf_USART1[7];
					temp=(temp<<8) + receBuf_USART1[6];
					if(crcData == temp)
					if(receBuf_USART1[1] == 4)
					{ 
						readInPutRegisters();
					}
					receCount_USART1 = 0;
				}	
			}      
			break;
		}
		case 5:
		{	 
			if(receCount_USART1 >= 8)  //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���8	���������һ������Ӧ�ùرս����ж�
			{ 
							test=6;
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)      
				{	  
					crcData = crc16(receBuf_USART1,6);
					temp=receBuf_USART1[7];
					temp=(temp<<8) + receBuf_USART1[6];
					if(crcData == temp)
					if(receBuf_USART1[1] == 5)
					{ 
						test=7;
						forceSingleCoil();//ǿ�õ�����Ȧ ״̬
					}
					receCount_USART1 = 0;
				}	
			}      
			break;
		}
		case 6:
		{
			if(receCount_USART1 >= 8)
			{    
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU) 
				{
					crcData = crc16(receBuf_USART1,6);
					temp=receBuf_USART1[7];
					temp=(temp<<8) + receBuf_USART1[6];
					if(crcData == temp)
					if(receBuf_USART1[1] == 6)
					{ 
						presetSingleRegister();      //Ԥ�õ������ּĴ���
					} 
					receCount_USART1 = 0;
				}	 
			}
			break;
		}
		case 15:
		{
			tempData = receBuf_USART1[6]; 
			tempData += 9; 
			if(receCount_USART1 >= tempData)
			{
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)
				{
					crcData = crc16(receBuf_USART1,tempData-2);
					if(crcData == (receBuf_USART1[tempData-1]<<8)+ receBuf_USART1[tempData-2])//�����ˣ���
					{
						forceMultipleCoils();  
					}
				} 
				receCount_USART1 = 0;
			}
			break;
        }
		case 16:						//���ö���Ĵ���
		{
			tempData = (receBuf_USART1[4]<<8) + receBuf_USART1[5];	 	//���üĴ�������
			tempData = tempData * 2; 						//���ݸ���Ӧ�õ��ڼĴ���*2
			tempData += 9;       //��ѯ�����ݰ���ʽ��֪��receCount_USART1Ӧ�õ���9+byteCount
			if(receCount_USART1 >= tempData)
			{  	
				if(receBuf_USART1[0] == Device_RWReg_Union.device.Address_ACU)
				{	 
					crcData = crc16(receBuf_USART1,tempData-2);
					temp=receBuf_USART1[tempData-1];
					temp=(temp<<8)+receBuf_USART1[tempData-2]; 
					if(crcData == temp)
					{  
						presetMultipleRegisters();  
					}
				} 
				receCount_USART1 = 0;
			}
			break; 
		}   
		default: break;  
		}
	}
}

void Begin_send_Upload(void)
{
//	b485Send = 1;      				//���ڷ���
	uart1sends(sendBuf_Upload,sendCount_Upload);
	
//	uart4sends(sendBuf_Upload,sendCount_Upload);//ͨ��485����
//	b485Send = 0;   	    		//�������485���ڽ���״̬
  
}
u8 ss=0;
void UpLoadData(void)
{
	u16 addr;
//	u16 tempAddr;
	u16 crcData;
//	u16 readCount;
	u16 byteCount=0;
	u16 i,j;
	u16 tempData = 0; 
	u16 byteCount_temp;
	
	//getRegisterVal(index_ACUAddress,&tempData);    //��ȡACU��ַ
	//sendBuf_USART1[i+3] = tempData >> 8;        
	//sendBuf_USART1[i+4] = tempData & 0xff;  
	//tempAddr = addr + RWDAT0;      				//���ּĴ���ƫ�Ƶ�ַRWDAT0��40000��
	//tempAddr = addr;      				//���ּĴ��� u16   RWReg[1034];��ַ���㿪ʼ
	for(i=0;i<Device_RWReg_Union.device.SensorTotalNum;i++)
	{
	 //i*3��Ϊ���������ò�������������AddressOffset_NumOfPerSensor��ַ��ʼ���
		//getRegisterVal(i*3+1+AddressOffset_NumOfPerSensor,&byteCount_temp);  //ÿ���������ڶ����ڴ��Ӧ�������ݸ��������͸�����
		//byteCount+=byteCount_temp*2;
		byteCount_temp = Device_RWReg_Union.device.sensor[i].data_quantity;	
		byteCount += byteCount_temp * 2;
		
		for(j=0;j<byteCount_temp;j++)
		{
			//getRegisterVal(i*Device_RWReg_Union.device.BytesPerSensor+j,&tempData);	
			
			tempData = RegisterMap_ReadData(43000+j+i*4);
			
			sendBuf_Upload[3+byteCount-(byteCount_temp-j)*2] = tempData >> 8;  					
	    sendBuf_Upload[4+byteCount-(byteCount_temp-j)*2] = tempData & 0xff;			
			
		}
	}
	
	addr =Device_RWReg_Union.device.Address_ACU;    //��ȡACU��ַ
	sendBuf_Upload[0] = addr;						//�豸��ַ
	sendBuf_Upload[1] = 3;  							//������ : 03
	sendBuf_Upload[2] = byteCount;						//���ּĴ���������Ӧ���ֽ�����
	sendBuf_Upload[2]=sendBuf_Upload[2]+3;//�����1���̵���״̬��2������IO״̬
	byteCount += 3;             				//����ǰ��ĵ�ַ�������룬��ַ ��3+byteCount���ֽ�
	
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.AllRelay_State;//������8���̵���״̬
	byteCount++;
	
	//*********������������16λ*************//
	
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.Input_State>>8;//��8λ
	byteCount++;
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.Input_State&0xff;//��8λ
	byteCount++;
	
	crcData = crc16(sendBuf_Upload,byteCount);			//����CRCУ����
	sendBuf_Upload[byteCount] = crcData & 0xff;   		//CRCУ�����λ��ǰ
	
	byteCount++;							    //CRCУ�����λ�ں�
	sendBuf_Upload[byteCount] = crcData >> 8 ;	   		//��λ�ں�
	
	sendCount_Upload = byteCount + 1;					//���ͳ�ȥ���ݸ���
	
	Begin_send_Upload();
	
}




