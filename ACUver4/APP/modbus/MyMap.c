#include "MyMap.h"


unsigned char Address_ACU = 0x01;
unsigned int SensorTotalNum = 3 ;
unsigned int BytesPerSensor = 4;//含一个地址，一个数据个数，两个数据
unsigned int WorkMod=0; //工作模式，0为被动读取，1为主动上传
unsigned int UploadPeriod=1000;  //主动上传时间间隔
