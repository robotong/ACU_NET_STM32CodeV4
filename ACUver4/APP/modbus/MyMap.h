
#ifndef __MYMAP_H
#define __MYMAP_H 
#include "stdint.h"

#define ConfigMemorysize 5
#define SensorMemorysize 8
#define SensorNumMax 32
//SensorRegisterNum = SensorMemorysize*SensorNumMax + ConfigMemorysize;
#define SensorRegisterNum 231

//����̵����ṹ��
typedef struct
{
  uint16_t mode; //����ģʽ��0�����Զ�ģʽ��1��������ģʽ��2����������ģʽ 3:�����ݻ�ģʽ��4����ģʽ
	uint16_t limit_up; //��������
	uint16_t limit_down; //��������
	//uint16_t whichData1; //��ͨ�ʹ���ģʽ�£�ѡ���ĸ�����������8λ���������ţ���8λ�����������ĸ�����
	//uint16_t whichData2; //��ͨ�ʹ���ģʽ�£�ѡ���ĸ�����������8λ���������ţ���8λ�����������ĸ�����
	
	//ÿ���̵��������4�����������ƣ�ÿ��������Դռ��8bit����32λ��whichdata1 �� whichdata2����
	//8λ�е�0λΪ�Ƿ�ʹ�ܸ������ݣ�
	//��1-2λ����ĳ���������ĵڼ���������Χ0-3��
	//��5λ�����ĸ�����������Χ0-31
	uint16_t whichData1; 
	uint16_t whichData2; 
	uint16_t polar; //�̵���������� 0��ͬ�� 1������
	uint16_t input_num; //������� 0~15 
	uint16_t state; //�̵���״̬
	
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
	uint16_t input; //����ڵ�ָʾ��
	uint8_t relay; //�̵���ָʾ��
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


/*�������ش������ṹ��*/
typedef struct
{
  uint16_t sensor_number; //���������
	uint16_t sensor_address; //���ش������ĵ�ַ //��������ַ
	uint16_t sensor_serialnumber; //���ش�������ţ�������ѯ��ʲô������ //���������к�
	uint16_t data_firstaddress; //���ش�����   //�����׵�ַ
	uint16_t data_quantity; //���ش���������������   //��������
	uint16_t data_reg_address; //������modbus�Ĵ����еĵ�ַ
	uint16_t sensor_state; //����������״̬
	uint16_t data[4]; 
} Sensor_TypeDef;

/*�豸�ṹ��*/
typedef struct
{
	uint16_t Address_ACU;
	uint16_t Address_ExternRS485;
	uint16_t SensorTotalNum;
	uint16_t WorkMod; //����ģʽ��0Ϊ������ȡ��1Ϊ�����ϴ�
	uint16_t UploadPeriod;  //�����ϴ�ʱ����
	uint16_t RS485_Sensor_Baud;
	uint16_t RS485_Extend_Baud;
	uint16_t RS485_4G_Baud;
	uint16_t ACU_State;
	uint16_t AllRelay_State;
	uint16_t Input_State;
	uint16_t RJ45Busy; //0:���У�1����sensor�ش�����ռ�ã�2������չ485�ӿڷ�������ռ��
	LED_Union_TypeDef LED_State;  			//����״̬��0-15λ���̵���16-23��״̬24-27//Display_LED=(InputData) | (((u32)Relay_State)<<16)|((u32)System_State<<24);
	Sensor_TypeDef sensor[SensorNumMax];
	RELAY_TypeDef relay[8];
} Device_TypeDef;



/*�豸�ṹ����Modbus������*/
typedef union
{
  uint16_t reg[sizeof(Device_TypeDef)/2]; 
  Device_TypeDef device;
} DeviceRegister__TypeDef;





extern unsigned char Address_ACU;
extern unsigned int  SensorTotalNum;
extern unsigned int  BytesPerSensor;//��һ����ַ��һ�����ݸ�������������
extern unsigned int  WorkMod; //����ģʽ��0Ϊ������ȡ��1Ϊ�����ϴ�
extern unsigned int  UploadPeriod;  //�����ϴ�ʱ����


#endif

