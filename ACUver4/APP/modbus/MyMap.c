#include "MyMap.h"


unsigned char Address_ACU = 0x01;
unsigned int SensorTotalNum = 3 ;
unsigned int BytesPerSensor = 4;//��һ����ַ��һ�����ݸ�������������
unsigned int WorkMod=0; //����ģʽ��0Ϊ������ȡ��1Ϊ�����ϴ�
unsigned int UploadPeriod=1000;  //�����ϴ�ʱ����
