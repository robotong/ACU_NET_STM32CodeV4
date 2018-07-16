
#ifndef __MYMAP_H
#define __MYMAP_H 
#include "stdint.h"

#define ConfigMemorysize 5
#define SensorMemorysize 8
#define SensorNumMax 32
//SensorRegisterNum = SensorMemorysize*SensorNumMax + ConfigMemorysize;
#define SensorRegisterNum 231

//定义继电器结构体
typedef struct
{
  uint16_t mode; //运行模式，0：非自动模式，1：单数据模式，2：多数据与模式 3:多数据或模式，4联动模式
	uint16_t limit_up; //动作上限
	uint16_t limit_down; //动作下限
	//uint16_t whichData1; //带通和带阻模式下，选择哪个传感器，高8位：传感器号，低8位：传感器中哪个数据
	//uint16_t whichData2; //带通和带阻模式下，选择哪个传感器，高8位：传感器号，低8位：传感器中哪个数据
	
	//每个继电器最多由4个数据来控制，每个数据来源占用8bit，共32位（whichdata1 和 whichdata2），
	//8位中第0位为是否使能该组数据，
	//第1-2位代表某个传感器的第几个数，范围0-3，
	//后5位代表哪个传感器，范围0-31
	uint16_t whichData1; 
	uint16_t whichData2; 
	uint16_t polar; //继电器输出极性 0：同相 1：反相
	uint16_t input_num; //联动标号 0~15 
	uint16_t state; //继电器状态
	
} RELAY_TypeDef;


typedef struct
{
	uint8_t systemrun:1;
	uint8_t systemerror:1;
	uint8_t sensorerror:1;
	uint8_t communicationerror:1;
	uint8_t reserved1:1;
	uint8_t reserved2:1;
	uint8_t reserved3:1;
	uint8_t reserved4:1;
	
} SystemStateLED_TypeDef;

typedef struct
{
	uint16_t input; //输入节点指示灯
	uint8_t relay; //继电器指示灯
	uint8_t systemrun:1;
	uint8_t systemerror:1;
	uint8_t sensorerror:1;
	uint8_t communicationerror:1;
	uint8_t reserved1:1;
	uint8_t reserved2:1;
	uint8_t reserved3:1;
	uint8_t reserved4:1;
} LED_TypeDef;


typedef union
{
  uint32_t all; 
  LED_TypeDef bits;
} LED_Union_TypeDef;


/*单个挂载传感器结构体*/
typedef struct
{
  uint16_t sensor_number; //传感器序号
	uint16_t sensor_address; //挂载传感器的地址 //传感器地址
	uint16_t sensor_serialnumber; //挂载传感器序号，用来查询是什么传感器 //传感器序列号
	uint16_t data_firstaddress; //挂载传感器   //数据首地址
	uint16_t data_quantity; //挂载传感器中数据数量   //数据数量
	uint16_t data_reg_address; //数据在modbus寄存器中的地址
	uint16_t sensor_state; //传感器在线状态
	uint16_t data[4]; 
} Sensor_TypeDef;

/*设备结构体*/
typedef struct
{
	uint16_t Address_ACU;
	uint16_t Address_ExternRS485;
	uint16_t SensorTotalNum;
	uint16_t WorkMod; //工作模式，0为被动读取，1为主动上传
	uint16_t UploadPeriod;  //主动上传时间间隔
	uint16_t RS485_Sensor_Baud;
	uint16_t RS485_Extend_Baud;
	uint16_t RS485_4G_Baud;
	uint16_t ACU_State;
	uint16_t AllRelay_State;
	uint16_t Input_State;
	uint16_t RJ45Busy; //0:空闲，1：被sensor回传数据占用，2：被扩展485接口发送数据占用
	LED_Union_TypeDef LED_State;  			//输入状态低0-15位，继电器16-23，状态24-27//Display_LED=(InputData) | (((u32)Relay_State)<<16)|((u32)System_State<<24);
	Sensor_TypeDef sensor[SensorNumMax];
	RELAY_TypeDef relay[8];
} Device_TypeDef;



/*设备结构体与Modbus共用体*/
typedef union
{
  uint16_t reg[sizeof(Device_TypeDef)/2]; 
  Device_TypeDef device;
} DeviceRegister__TypeDef;





extern unsigned char Address_ACU;
extern unsigned int  SensorTotalNum;
extern unsigned int  BytesPerSensor;//含一个地址，一个数据个数，两个数据
extern unsigned int  WorkMod; //工作模式，0为被动读取，1为主动上传
extern unsigned int  UploadPeriod;  //主动上传时间间隔


#endif

