#include "MODBUS.h"
#include "RESISTER.h"
#include "MODBUS_CRC.h"
#include "flash.h"
u16 b=0;
u16 test2=0;
u16 test3=0;
u8 test=0;
	u8 LocalAddr = 0x01; 								   //从机地址，默认为0X01

	u8   receTimeOut_USART1;            	     		 //接收超时
	u8   sendCount;  			 		 						 //发送出去字节个数
	u8   receCount_USART1;    		  			 				 //接收到的字节个数
	u8   receBuf_USART1[50];
	u8   sendBuf_USART1[50];
	
	u8   receBuf_USART4[50];
	u8   sendBuf_USART4[50];
	u8   receCount_USART4; 
	
	
	
	u8   sendPosi;	    			     				 //发送位置

	u8   sendBuf_Upload[280];
	u8   sendCount_Upload;

uint32_t BAUDtable[] = {9600,14400,19200,38400,56000,57600,115200};

 /**
 * 函数名：InitProg_485
 * 描述  ：初始化函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
		485收发控制引脚
    低电平接收模式
    高电平发送模式
  */
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//	GPIO_SetBits(GPIOC,GPIO_Pin_9);
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	
	USART1_Config(115200);     		//串口1 初始化  波特率9600  无校验
	USART2_Config(BAUDtable[Device_RWReg_Union.device.RS485_Sensor_Baud]); //读取传感器用
	UART4_Config(BAUDtable[Device_RWReg_Union.device.RS485_Extend_Baud]); //连接外扩设备
//		USART2_Config(9600); 
//	UART4_Config(9600); 
	TIM2_Configuration();		//初始化定时器2  1MS
	//Address_ACU = Addr;       //配置从机地址
} 

/**
 * 函数名：uart1sends
 * 描述  ：发送函数,向网口发送
 * 输入  ：buff 数组  len 长度
 * 输出  ：无
 * 调用  ：内部调用
 * 作者  :YaoTong 2017
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
 * 函数名：uart1sends
 * 描述  ：发送函数,向扩展的RS485发送数据
 * 输入  ：buff 数组  len 长度
 * 输出  ：无
 * 调用  ：内部调用
 * 作者  :YaoTong 2017
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
//发送数据到扩展RS485接口
void SendDataToExternRS485(void)
{
  //只要地址匹配，从网线接收到什镁痛发送什么扩展RS485接口
	uart4sends(receBuf_USART1,8);
}
*/


/**
 * 函数名：Begin_send
 * 描述  ：串口发送函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
void Begin_send(void)
{
//	b485Send = 1;      				//处于发送
	uart1sends(sendBuf_USART1,sendCount);
//	b485Send = 0;   	    		//发送完后将485置于接收状态
  receCount_USART1 = 0;          	//清接收地址偏移寄存器
}


/**
 * 函数名：readCoils
 * 描述  ：读单个或多个线圈状态  fuction:01
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	bitCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; //读取的位个数
	byteCount = bitCount / 8;    			 //字节个数
	if(bitCount%8 != 0)
	byteCount++;       
	for(k=0;k<byteCount;k++)				 //字节位置
	{
		position = k + 3;
		sendBuf_USART1[position] = 0;
		for(i=0;i<8;i++)
		{
			getCoilVal(tempAddr,&tempData);
			
			sendBuf_USART1[position] |= tempData << i;
			tempAddr++;
			if(tempAddr >= (addr+bitCount))  //读完
			{ 
				exit = 1;
				break;
			} 
		}
		if(exit == 1)
		break;
	}
	test=3;
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;                 //设备地址
	sendBuf_USART1[1] = 1; 						//功能码 : 1
	sendBuf_USART1[2] = byteCount;       			//线圈数量对应的字节数
	byteCount += 3;							
	crcData = crc16(sendBuf_USART1,byteCount);		//生成CRC校验码 
	sendBuf_USART1[byteCount] = crcData & 0xff;	//CRC校验码低位在前
	byteCount++;							
	sendBuf_USART1[byteCount] = crcData >> 8;		//CRC校验码高位在后
	sendCount = byteCount + 1;				//发送出去数据个数
	Begin_send();   
}	

/**
 * 函数名：readInPutCoils
 * 描述  ：读取线圈输入（只读寄存器）状态  fuction:02
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	//只读线圈寄存器偏移地址ROSTATUES0（10000）
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
			//读完,加上寄存器的偏移地址
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
	//离散状态数量对应的字节数	
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
 * 函数名：readRegisters
 * 描述  ：读取多个寄存器值  fuction:03
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	tempAddr = addr + RWDAT0;      				//保持寄存器偏移地址RWDAT0（40000）
	//tempAddr = addr;      				//保持寄存器 u16   RWReg[1034];地址从零开始
	readCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 	//要读的个数 ,整型
	byteCount = readCount * 2;                  //每个寄存器内容占高，低两个字节
	test3 = tempAddr;
	for(i=0;i<byteCount;i+=2,tempAddr++)
	{
		//getRegisterVal(tempAddr,&tempData); 
		
		test2= RegisterMap_ReadData(41000);
		tempData = RegisterMap_ReadData(tempAddr);
		sendBuf_USART1[i+3] = tempData >> 8;        
		sendBuf_USART1[i+4] = tempData & 0xff;  
	}
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;						//设备地址
	sendBuf_USART1[1] = 3;  							//功能码 : 03
	sendBuf_USART1[2] = byteCount;						//保持寄存器数量对应的字节数
	byteCount += 3;             				//加上前面的地址，功能码，地址 共3+byteCount个字节
	crcData = crc16(sendBuf_USART1,byteCount);			//生成CRC校验码
	sendBuf_USART1[byteCount] = crcData & 0xff;   		//CRC校验码低位在前
	byteCount++;							    //CRC校验码高位在后
	sendBuf_USART1[byteCount] = crcData >> 8 ;	   		//高位在后
	sendCount = byteCount + 1;					//发送出去数据个数
	Begin_send();
}

/**
 * 函数名：readInPutRegisters
 * 描述  ：读取输入寄存器  fuction:04
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	tempAddr = addr + RODAT0;  					//输入寄存器偏移地址RODAT0（30000）
	readCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 	//要读的个数 ,整型
	byteCount = readCount * 2;                  //每个寄存器内容占高，低两个字节
	
	for(i=0;i<byteCount;i+=2,tempAddr++)
	{
		getRegisterVal(tempAddr,&tempData);    
		sendBuf_USART1[i+3] = tempData >> 8;        
		sendBuf_USART1[i+4] = tempData & 0xff;  
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;					//设备地址
	sendBuf_USART1[1] = 4;  						//功能码 : 04
	sendBuf_USART1[2] = byteCount;					//输入寄存器数量对应的字节数
	byteCount += 3;             			//加上前面的地址，功能码，地址 共3+byteCount个字节
	crcData = crc16(sendBuf_USART1,byteCount);		//生成CRC校验码
	sendBuf_USART1[byteCount] = crcData & 0xff;   	//CRC校验码低位在前
	byteCount++;
	sendBuf_USART1[byteCount] = crcData >> 8 ;	   	//CRC校验码高位在后
	sendCount = byteCount + 1;				//发送出去数据个数
	Begin_send();
}
	 
/**
 * 函数名：forceSingleCoil
 * 描述  ：强制单个线圈  fuction:05
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	
	/*设为ON*/
	if(onOff == 0xff00)
	{ 
	    tempData = 1;
	} 
	/*设为OFF*/
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
 * 函数名：presetSingleRegister
 * 描述  ：设置单个寄存器  fuction:06
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
void presetSingleRegister(void)
{
	u16 addr;
	u16 tempAddr;
	u16 tempData;
	u16 crcData;
	
	addr = (receBuf_USART1[2]<<8) + receBuf_USART1[3];
	tempAddr = addr + RWDAT0;      				//保持寄存器偏移地址RWDAT0（40000）
	//tempAddr = addr;      				//保持寄存器偏移地0
	b=tempAddr;
	tempData = (receBuf_USART1[4]<<8) + receBuf_USART1[5];
	b = tempData;
	RegisterMap_WriteData(tempAddr,tempData);
	//setRegisterVal(tempAddr,tempData); 
	//当为配置数据时，向flash存储一次
	if(addr>1023)
	{
		WriteDataToFlash(64,160,8);
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//设备地址
	sendBuf_USART1[1] = 6;    				//功能码 : 06
	sendBuf_USART1[2] = addr >> 8;  		//寄存器地址高位
	sendBuf_USART1[3] = addr & 0xff;		//寄存器地址低位
	sendBuf_USART1[4] =receBuf_USART1[4];			//寄存器数值
	sendBuf_USART1[5] =receBuf_USART1[5];			//寄存器数值
	crcData = crc16(sendBuf_USART1,6);		//生成CRC校验码
	sendBuf_USART1[6] = crcData & 0xff;  	//CRC校验码低位在前
	sendBuf_USART1[7] = crcData >> 8;	  	//CRC校验码高位在后
	sendCount = 8;					////发送出去数据个数
	Begin_send(); 
}

/**
 * 函数名：forceMultipleCoils
 * 描述  ：强置多线圈值  fuction:15
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	byteCount = bitCount / 8;    //字节个数
	if(bitCount%8 != 0)
	byteCount++;
	
	for(k=0;k<byteCount;k++)    //字节位置
	{
			for(i=0;i<8;i++)
			{
					tempData = (receBuf_USART1[k+7] >> i)&0x01;  
					setCoilVal(tempAddr,tempData); 
					tempAddr++;
					if(tempAddr >= (addr + bitCount + 8))//读完
					{ 
						exit = 1;
						break;
					} 
			}
			if(exit == 1)
			break;
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//设备地址
	sendBuf_USART1[1] = 15;    			//功能码 : 15
	sendBuf_USART1[2] = addr >> 8;  		//寄存器地址高位
	sendBuf_USART1[3] = addr & 0xff;		//寄存器地址低位
	sendBuf_USART1[4] = bitCount >> 8;		//待设置寄存器数量高位
	sendBuf_USART1[5] = bitCount & 0xff;	//待设置寄存器数量低位
	crcData = crc16(sendBuf_USART1,6);		//生成CRC校验码
	sendBuf_USART1[6] = crcData & 0xff;  	//CRC校验码低位在前
	sendBuf_USART1[7] = crcData >> 8;	  	//CRC校验码高位在后
	sendCount = 8;					//发送出去数据个数
	Begin_send(); 
}

/**
 * 函数名：presetMultipleRegisters
 * 描述  ：设置多个寄存器值  fuction:16
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
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
	tempAddr = addr + RWDAT0;      				//保持寄存器偏移地址RWDAT0（40000）
	//tempAddr = addr;
	setCount = (receBuf_USART1[4]<<8) + receBuf_USART1[5]; 
	for(i=0;i<setCount;i++,tempAddr++)
	{
		tempData = (receBuf_USART1[i*2+7]<<8) + receBuf_USART1[i*2+8];//待设置寄存器值
		//setRegisterVal(tempAddr,tempData);  
		RegisterMap_WriteData(tempAddr,tempData);
	}
	//当为配置数据时，向flash存储一次
	if(addr>1023)
	{
		WriteDataToFlash(64,160,8);
	}
	
	sendBuf_USART1[0] = Device_RWReg_Union.device.Address_ACU;			//设备地址
	sendBuf_USART1[1] = 16;    			//功能码 : 16
	sendBuf_USART1[2] = addr >> 8;  		//寄存器地址高位
	sendBuf_USART1[3] = addr & 0xff;		//寄存器地址低位
	sendBuf_USART1[4] = setCount >> 8;		//待设置寄存器数量高位
	sendBuf_USART1[5] = setCount & 0xff;	//待设置寄存器数量低位
	crcData = crc16(sendBuf_USART1,6);		//生成CRC校验码
	sendBuf_USART1[6] = crcData & 0xff;  	//CRC校验码低位在前
	sendBuf_USART1[7] = crcData >> 8;	  	//CRC校验码高位在后
	sendCount = 8;					//发送出去数据个数
	Begin_send(); 
}


/**
 * 函数名：checkComm0Modbus
 * 描述  ：查询uart接收的数据包内容函数
 *         丛机根据串口接收到的数据包receBuf_USART1[1]里面的内容，
 *         即function code执行相应的命令
 *         10ms内必须响应接收数据
 * 输入  ：
 * 输出  ：
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
void checkComm0Modbus(void)		   
{
	u16 crcData;
	u16 tempData;
	u16 temp;
	
	if(receCount_USART1 > 4)		 //如果接收到数据个数大于4个
	{	 
		switch(receBuf_USART1[1])
		{
			case 0xff:
			{	 
				if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
				if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
				if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
			if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
			if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
			if(receCount_USART1 >= 8)  //从询问数据包格式可知，receCount_USART1应该等于8	，接收完成一组数据应该关闭接收中断
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
						forceSingleCoil();//强置单个线圈 状态
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
						presetSingleRegister();      //预置单个保持寄存器
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
					if(crcData == (receBuf_USART1[tempData-1]<<8)+ receBuf_USART1[tempData-2])//更改了？？
					{
						forceMultipleCoils();  
					}
				} 
				receCount_USART1 = 0;
			}
			break;
        }
		case 16:						//设置多个寄存器
		{
			tempData = (receBuf_USART1[4]<<8) + receBuf_USART1[5];	 	//设置寄存器个数
			tempData = tempData * 2; 						//数据个数应该等于寄存器*2
			tempData += 9;       //从询问数据包格式可知，receCount_USART1应该等于9+byteCount
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
//	b485Send = 1;      				//处于发送
	uart1sends(sendBuf_Upload,sendCount_Upload);
	
//	uart4sends(sendBuf_Upload,sendCount_Upload);//通过485传递
//	b485Send = 0;   	    		//发送完后将485置于接收状态
  
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
	
	//getRegisterVal(index_ACUAddress,&tempData);    //获取ACU地址
	//sendBuf_USART1[i+3] = tempData >> 8;        
	//sendBuf_USART1[i+4] = tempData & 0xff;  
	//tempAddr = addr + RWDAT0;      				//保持寄存器偏移地址RWDAT0（40000）
	//tempAddr = addr;      				//保持寄存器 u16   RWReg[1034];地址从零开始
	for(i=0;i<Device_RWReg_Union.device.SensorTotalNum;i++)
	{
	 //i*3因为传感器配置参数有三个，从AddressOffset_NumOfPerSensor地址开始存放
		//getRegisterVal(i*3+1+AddressOffset_NumOfPerSensor,&byteCount_temp);  //每个传感器第二个内存对应的是数据个数（整型个数）
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
	
	addr =Device_RWReg_Union.device.Address_ACU;    //获取ACU地址
	sendBuf_Upload[0] = addr;						//设备地址
	sendBuf_Upload[1] = 3;  							//功能码 : 03
	sendBuf_Upload[2] = byteCount;						//保持寄存器数量对应的字节数，
	sendBuf_Upload[2]=sendBuf_Upload[2]+3;//多加入1个继电器状态，2个输入IO状态
	byteCount += 3;             				//加上前面的地址，功能码，地址 共3+byteCount个字节
	
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.AllRelay_State;//最后加入8个继电器状态
	byteCount++;
	
	//*********加入输入数据16位*************//
	
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.Input_State>>8;//高8位
	byteCount++;
	sendBuf_Upload[byteCount]=Device_RWReg_Union.device.Input_State&0xff;//低8位
	byteCount++;
	
	crcData = crc16(sendBuf_Upload,byteCount);			//生成CRC校验码
	sendBuf_Upload[byteCount] = crcData & 0xff;   		//CRC校验码低位在前
	
	byteCount++;							    //CRC校验码高位在后
	sendBuf_Upload[byteCount] = crcData >> 8 ;	   		//高位在后
	
	sendCount_Upload = byteCount + 1;					//发送出去数据个数
	
	Begin_send_Upload();
	
}




