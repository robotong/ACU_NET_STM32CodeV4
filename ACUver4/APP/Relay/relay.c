#include "DIO.h"
#include "HC595.h"
#include "RESISTER.h"
#include "MyMap.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define RELAY0 BIT0
#define RELAY1 BIT1
#define RELAY2 BIT2
#define RELAY3 BIT3
#define RELAY4 BIT4
#define RELAY5 BIT5
#define RELAY6 BIT6
#define RELAY7 BIT7

#define RELAY_RUNMODE_Manual 0
#define RELAY_RUNMODE_SingleData 1
#define RELAY_RUNMODE_MultiData_AND 2
#define RELAY_RUNMODE_MultiData_OR 3
#define RELAY_RUNMODE_Link 4

#define RELAY_ON  0x0001
#define RELAY_OFF 0x0000
#define RELAY_SamePhase 0
#define RELAY_InvertPhase 1

unsigned char RelaySet=0;

/**
  ******************************************************************************
  * @file    relay.c
  * @author  YaoTong
  * @version V4.0
  * @date    2017-7-1
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *含有
  *
  *
  ******************************************************************************
  */
uint8_t SingleRelayControl(DeviceRegister__TypeDef *device_acu, uint8_t whichRelay)
{
    uint8_t whichSensor[4];
    uint8_t whichData[4];
    uint8_t whichDataON[4]={0}; //哪个数据被启用，共4个
    static uint8_t FourData_MiddleData[4]={0};
    uint16_t limitup;
    uint16_t limitdown;
    uint16_t data[4];




    limitup = device_acu->device.relay[whichRelay].limit_up;
    limitdown = device_acu->device.relay[whichRelay].limit_down;

    whichDataON[0] = (device_acu->device.relay[whichRelay].whichData1 & 0x0001)?1:0 ; //如果该数据被启用，则置1
    whichDataON[1] = (device_acu->device.relay[whichRelay].whichData1 & 0x0100)?1:0 ;
    whichDataON[2] = (device_acu->device.relay[whichRelay].whichData2 & 0x0001)?1:0 ;
    whichDataON[3] = (device_acu->device.relay[whichRelay].whichData2 & 0x0100)?1:0 ;

    /************第0个传感器数据**************/
    if(whichDataON[0] || (device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_SingleData)) //该组数据被启用，用来控制继电器
    {
          //哪个传感器的哪个数据作为继电器自动开关数据源  
			whichSensor[0] = (device_acu->device.relay[whichRelay].whichData1 >> 3) & 0x001F;
        whichData[0]   = (device_acu->device.relay[whichRelay].whichData1 >> 1) & 0x0003;
        data[0] = device_acu->device.sensor[whichSensor[0]].data[whichData[0]];
        if( data[0] > limitup )
        {
            FourData_MiddleData[0] = 1;
        }
        else if( data[0] < limitdown )
        {
            FourData_MiddleData[0] = 0;
        }
    }
    else
    {
        if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_AND)
        {
            FourData_MiddleData[0] = 1;
        }
        else if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_OR)
        {
            FourData_MiddleData[0] = 0;
        }
    }

    /************第1个传感器数据**************/
    if(whichDataON[1]) //该组数据被启用，用来控制继电器
    {
        whichSensor[1] = (device_acu->device.relay[whichRelay].whichData1 >> 11) & 0x001F;
        whichData[1]   = (device_acu->device.relay[whichRelay].whichData1 >> 9) & 0x0003;
        data[1] = device_acu->device.sensor[whichSensor[1]].data[whichData[1]];
        if( data[1] > limitup )
        {
            FourData_MiddleData[1] = 1;
        }
        else if( data[1] < limitdown )
        {
            FourData_MiddleData[1] = 0;
        }
    }
    else
    {
        if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_AND)
        {
            FourData_MiddleData[1] = 1;
        }
        else if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_OR)
        {
            FourData_MiddleData[1] = 0;
        }
    }

    /************第2个传感器数据**************/
    if(whichDataON[2]) //该组数据被启用，用来控制继电器
    {
        whichSensor[2] = (device_acu->device.relay[whichRelay].whichData1 >> 3) & 0x001F;
        whichData[2]   = (device_acu->device.relay[whichRelay].whichData1 >> 1) & 0x0003;
        data[2] = device_acu->device.sensor[whichSensor[2]].data[whichData[2]];
        if( data[2] > limitup )
        {
            FourData_MiddleData[2] = 1;
        }
        else if( data[2] < limitdown )
        {
            FourData_MiddleData[2] = 0;
        }
    }
    else
    {
        if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_AND)
        {
            FourData_MiddleData[2] = 1;
        }
        else if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_OR)
        {
            FourData_MiddleData[2] = 0;
        }
    }

    /************第3个传感器数据**************/
    if(whichDataON[3]) //该组数据被启用，用来控制继电器
    {
        whichSensor[3] = (device_acu->device.relay[whichRelay].whichData1 >> 11) & 0x001F;
        whichData[3]   = (device_acu->device.relay[whichRelay].whichData1 >> 9) & 0x0003;
        data[3] = device_acu->device.sensor[whichSensor[3]].data[whichData[3]];
        if( data[3] > limitup )
        {
            FourData_MiddleData[3] = 1;
        }
        else if( data[3] < limitdown )
        {
            FourData_MiddleData[3] = 0;
        }
    }
    else
    {
        if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_AND)
        {
            FourData_MiddleData[3] = 1;
        }
        else if(device_acu->device.relay[whichRelay].mode == RELAY_RUNMODE_MultiData_OR)
        {
            FourData_MiddleData[3] = 0;
        }
    }

    switch(device_acu->device.relay[whichRelay].mode)
    {
    case RELAY_RUNMODE_Manual:

        break;
    case RELAY_RUNMODE_MultiData_AND:

        if((FourData_MiddleData[0] & FourData_MiddleData[1] & FourData_MiddleData[2] & FourData_MiddleData[3]) 
					  && (whichDataON[0] | whichDataON[1] | whichDataON[2] | whichDataON[3]) )  //&& (whichDataON[0] | whichDataON[1] | whichDataON[2] | whichDataON[3])z去除都没启用的情况
        {
            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_ON;
            else
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
        }
        else
        {
            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
            else
                device_acu->device.relay[whichRelay].state = RELAY_ON;
        }
        break;
				
    case RELAY_RUNMODE_MultiData_OR:
        if((FourData_MiddleData[0] | FourData_MiddleData[1] | FourData_MiddleData[2] | FourData_MiddleData[3]) && (whichDataON[0] | whichDataON[1] | whichDataON[2] | whichDataON[3]))
        {
            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_ON;
            else
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
        }
        else
        {
            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
            else
                device_acu->device.relay[whichRelay].state = RELAY_ON;
        }
        break;
				
    case RELAY_RUNMODE_Link:
        if(device_acu->device.Input_State & (0x0001 << (device_acu->device.relay[whichRelay].input_num))) //继电器与哪个输入节点进行联动，
        {
            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_ON;
            else
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
        }
        else
        {

            if(device_acu->device.relay[whichRelay].polar == RELAY_SamePhase)
                device_acu->device.relay[whichRelay].state = RELAY_OFF;
            else
                device_acu->device.relay[whichRelay].state = RELAY_ON;
        }
        break;
		default :break;
    }

    return 0;
}
//8个继电器的状态控制
void AllRelayControl(DeviceRegister__TypeDef *device_acu)
{
    unsigned char i;
    for(i=0; i<8; i++)
    {
        SingleRelayControl(device_acu, i);
    }

}





//继电器动作，LED显示更新
void RelayAndLedUpdate(DeviceRegister__TypeDef *device_acu)
{
    //继电器状态合并
    device_acu->device.AllRelay_State = device_acu->device.relay[0].state +
                                        (device_acu->device.relay[1].state * 2) +
                                        (device_acu->device.relay[2].state * 4) +
                                        (device_acu->device.relay[3].state * 8) +
                                        (device_acu->device.relay[4].state * 16) +
                                        (device_acu->device.relay[5].state * 32) +
                                        (device_acu->device.relay[6].state * 64) +
                                        (device_acu->device.relay[7].state * 128) ;
    //LED灯状态合并
    device_acu->device.LED_State.bits.input = device_acu->device.Input_State;
    device_acu->device.LED_State.bits.relay = device_acu->device.AllRelay_State;

    WR_595_8bits((unsigned char)(device_acu->device.AllRelay_State)); //继电器控制
    LED_WR_595_28bits_YAO(~device_acu->device.LED_State.all); //LED显示控制,逻辑为低电平亮灯，所以取反
}




void RelayInit(void)
{
    HC595_Init();
    Device_RWReg_Union.device.AllRelay_State = 0;
    Device_RWReg_Union.device.relay[0].state = 0;
    Device_RWReg_Union.device.relay[1].state = 0;
    Device_RWReg_Union.device.relay[2].state = 0;
    Device_RWReg_Union.device.relay[3].state = 0;
    Device_RWReg_Union.device.relay[4].state = 0;
    Device_RWReg_Union.device.relay[5].state = 0;
    Device_RWReg_Union.device.relay[6].state = 0;
    Device_RWReg_Union.device.relay[7].state = 0;

    RelaySet=0;
    LED_WR_595_28bits_YAO(0x0000);
}


void Relay0_ON(void)
{
    RelaySet|=RELAY0;
    WR_595_8bits(RelaySet);
}
void Relay0_OFF(void)
{
    RelaySet&=(~RELAY0);
    WR_595_8bits(RelaySet);
}

void Relay1_ON(void)
{
    RelaySet|=RELAY1;
    WR_595_8bits(RelaySet);
}

void Relay1_OFF(void)
{
    RelaySet&=(~RELAY1);
    WR_595_8bits(RelaySet);
}


void Relay2_ON(void)
{
    RelaySet|=RELAY2;
    WR_595_8bits(RelaySet);
}

void Relay2_OFF(void)
{
    RelaySet&=(~RELAY2);
    WR_595_8bits(RelaySet);
}

void Relay3_ON(void)
{
    RelaySet|=RELAY3;
    WR_595_8bits(RelaySet);
}

void Relay3_OFF(void)
{
    RelaySet&=(~RELAY3);
    WR_595_8bits(RelaySet);
}
void Relay4_ON(void)
{
    RelaySet|=RELAY4;
    WR_595_8bits(RelaySet);
}

void Relay4_OFF(void)
{
    RelaySet&=(~RELAY4);
    WR_595_8bits(RelaySet);
}

void Relay5_ON(void)
{
    RelaySet|=RELAY5;
    WR_595_8bits(RelaySet);
}

void Relay5_OFF(void)
{
    RelaySet&=(~RELAY5);
    WR_595_8bits(RelaySet);
}

void Relay6_ON(void)
{
    RelaySet|=RELAY6;
    WR_595_8bits(RelaySet);
}

void Relay6_OFF(void)
{
    RelaySet&=(~RELAY6);
    WR_595_8bits(RelaySet);
}
void Relay7_ON(void)
{
    RelaySet|=RELAY7;
    WR_595_8bits(RelaySet);
}

void Relay7_OFF(void)
{
    RelaySet&=(~RELAY7);
    WR_595_8bits(RelaySet);
}

