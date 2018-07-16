#include "RESISTER.h"
#include "DIO.h"
#include "HC595.h"
#include "relay.h"
#include "MyMap.h"

DeviceRegister__TypeDef Device_RWReg_Union;
extern uint32_t BAUDtable[];

//ding定义映射表
uint16_t* const Register41000[]=
{
	&Device_RWReg_Union.device.relay[0].mode,
	&Device_RWReg_Union.device.relay[0].limit_up,
	&Device_RWReg_Union.device.relay[0].limit_down,
	&Device_RWReg_Union.device.relay[0].whichData1,
	&Device_RWReg_Union.device.relay[0].whichData2,
	&Device_RWReg_Union.device.relay[0].polar,
	&Device_RWReg_Union.device.relay[0].input_num,
	&Device_RWReg_Union.device.relay[0].state,
	&Device_RWReg_Union.device.relay[1].mode,
	&Device_RWReg_Union.device.relay[1].limit_up,
	&Device_RWReg_Union.device.relay[1].limit_down,
	&Device_RWReg_Union.device.relay[1].whichData1,
	&Device_RWReg_Union.device.relay[1].whichData2,
	&Device_RWReg_Union.device.relay[1].polar,
	&Device_RWReg_Union.device.relay[1].input_num,
	&Device_RWReg_Union.device.relay[1].state,
	&Device_RWReg_Union.device.relay[2].mode,
	&Device_RWReg_Union.device.relay[2].limit_up,
	&Device_RWReg_Union.device.relay[2].limit_down,
	&Device_RWReg_Union.device.relay[2].whichData1,
	&Device_RWReg_Union.device.relay[2].whichData2,
	&Device_RWReg_Union.device.relay[2].polar,
	&Device_RWReg_Union.device.relay[2].input_num,
	&Device_RWReg_Union.device.relay[2].state,
	&Device_RWReg_Union.device.relay[3].mode,
	&Device_RWReg_Union.device.relay[3].limit_up,
	&Device_RWReg_Union.device.relay[3].limit_down,
	&Device_RWReg_Union.device.relay[3].whichData1,
	&Device_RWReg_Union.device.relay[3].whichData2,
	&Device_RWReg_Union.device.relay[3].polar,
	&Device_RWReg_Union.device.relay[3].input_num,
	&Device_RWReg_Union.device.relay[3].state,
		&Device_RWReg_Union.device.relay[4].mode,
	&Device_RWReg_Union.device.relay[4].limit_up,
	&Device_RWReg_Union.device.relay[4].limit_down,
	&Device_RWReg_Union.device.relay[4].whichData1,
	&Device_RWReg_Union.device.relay[4].whichData2,
	&Device_RWReg_Union.device.relay[4].polar,
	&Device_RWReg_Union.device.relay[4].input_num,
	&Device_RWReg_Union.device.relay[4].state,
		&Device_RWReg_Union.device.relay[5].mode,
	&Device_RWReg_Union.device.relay[5].limit_up,
	&Device_RWReg_Union.device.relay[5].limit_down,
	&Device_RWReg_Union.device.relay[5].whichData1,
	&Device_RWReg_Union.device.relay[5].whichData2,
	&Device_RWReg_Union.device.relay[5].polar,
	&Device_RWReg_Union.device.relay[5].input_num,
	&Device_RWReg_Union.device.relay[5].state,
		&Device_RWReg_Union.device.relay[6].mode,
	&Device_RWReg_Union.device.relay[6].limit_up,
	&Device_RWReg_Union.device.relay[6].limit_down,
	&Device_RWReg_Union.device.relay[6].whichData1,
	&Device_RWReg_Union.device.relay[6].whichData2,
	&Device_RWReg_Union.device.relay[6].polar,
	&Device_RWReg_Union.device.relay[6].input_num,
	&Device_RWReg_Union.device.relay[6].state,
		&Device_RWReg_Union.device.relay[7].mode,
	&Device_RWReg_Union.device.relay[7].limit_up,
	&Device_RWReg_Union.device.relay[7].limit_down,
	&Device_RWReg_Union.device.relay[7].whichData1,
	&Device_RWReg_Union.device.relay[7].whichData2,
	&Device_RWReg_Union.device.relay[7].polar,
	&Device_RWReg_Union.device.relay[7].input_num,
	&Device_RWReg_Union.device.relay[7].state

};

uint16_t* const Register42000[]=
{
	&Device_RWReg_Union.device.sensor[0].sensor_number,
	&Device_RWReg_Union.device.sensor[0].sensor_address,
	&Device_RWReg_Union.device.sensor[0].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[0].data_firstaddress,
	&Device_RWReg_Union.device.sensor[0].data_quantity,
		&Device_RWReg_Union.device.sensor[1].sensor_number,
	&Device_RWReg_Union.device.sensor[1].sensor_address,
	&Device_RWReg_Union.device.sensor[1].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[1].data_firstaddress,
	&Device_RWReg_Union.device.sensor[1].data_quantity,
		&Device_RWReg_Union.device.sensor[2].sensor_number,
	&Device_RWReg_Union.device.sensor[2].sensor_address,
	&Device_RWReg_Union.device.sensor[2].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[2].data_firstaddress,
	&Device_RWReg_Union.device.sensor[2].data_quantity,
		&Device_RWReg_Union.device.sensor[3].sensor_number,
	&Device_RWReg_Union.device.sensor[3].sensor_address,
	&Device_RWReg_Union.device.sensor[3].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[3].data_firstaddress,
	&Device_RWReg_Union.device.sensor[3].data_quantity,
		&Device_RWReg_Union.device.sensor[4].sensor_number,
	&Device_RWReg_Union.device.sensor[4].sensor_address,
	&Device_RWReg_Union.device.sensor[4].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[4].data_firstaddress,
	&Device_RWReg_Union.device.sensor[4].data_quantity,
		&Device_RWReg_Union.device.sensor[5].sensor_number,
	&Device_RWReg_Union.device.sensor[5].sensor_address,
	&Device_RWReg_Union.device.sensor[5].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[5].data_firstaddress,
	&Device_RWReg_Union.device.sensor[5].data_quantity,
		&Device_RWReg_Union.device.sensor[6].sensor_number,
	&Device_RWReg_Union.device.sensor[6].sensor_address,
	&Device_RWReg_Union.device.sensor[6].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[6].data_firstaddress,
	&Device_RWReg_Union.device.sensor[6].data_quantity,
		&Device_RWReg_Union.device.sensor[7].sensor_number,
	&Device_RWReg_Union.device.sensor[7].sensor_address,
	&Device_RWReg_Union.device.sensor[7].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[7].data_firstaddress,
	&Device_RWReg_Union.device.sensor[7].data_quantity,
		&Device_RWReg_Union.device.sensor[8].sensor_number,
	&Device_RWReg_Union.device.sensor[8].sensor_address,
	&Device_RWReg_Union.device.sensor[8].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[8].data_firstaddress,
	&Device_RWReg_Union.device.sensor[8].data_quantity,
		&Device_RWReg_Union.device.sensor[9].sensor_number,
	&Device_RWReg_Union.device.sensor[9].sensor_address,
	&Device_RWReg_Union.device.sensor[9].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[9].data_firstaddress,
	&Device_RWReg_Union.device.sensor[9].data_quantity,
		&Device_RWReg_Union.device.sensor[10].sensor_number,
	&Device_RWReg_Union.device.sensor[10].sensor_address,
	&Device_RWReg_Union.device.sensor[10].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[10].data_firstaddress,
	&Device_RWReg_Union.device.sensor[10].data_quantity,
		&Device_RWReg_Union.device.sensor[11].sensor_number,
	&Device_RWReg_Union.device.sensor[11].sensor_address,
	&Device_RWReg_Union.device.sensor[11].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[11].data_firstaddress,
	&Device_RWReg_Union.device.sensor[11].data_quantity,
		&Device_RWReg_Union.device.sensor[12].sensor_number,
	&Device_RWReg_Union.device.sensor[12].sensor_address,
	&Device_RWReg_Union.device.sensor[12].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[12].data_firstaddress,
	&Device_RWReg_Union.device.sensor[12].data_quantity,
		&Device_RWReg_Union.device.sensor[13].sensor_number,
	&Device_RWReg_Union.device.sensor[13].sensor_address,
	&Device_RWReg_Union.device.sensor[13].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[13].data_firstaddress,
	&Device_RWReg_Union.device.sensor[13].data_quantity,
		&Device_RWReg_Union.device.sensor[14].sensor_number,
	&Device_RWReg_Union.device.sensor[14].sensor_address,
	&Device_RWReg_Union.device.sensor[14].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[14].data_firstaddress,
	&Device_RWReg_Union.device.sensor[14].data_quantity,
		&Device_RWReg_Union.device.sensor[15].sensor_number,
	&Device_RWReg_Union.device.sensor[15].sensor_address,
	&Device_RWReg_Union.device.sensor[15].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[15].data_firstaddress,
	&Device_RWReg_Union.device.sensor[15].data_quantity,
		&Device_RWReg_Union.device.sensor[16].sensor_number,
	&Device_RWReg_Union.device.sensor[16].sensor_address,
	&Device_RWReg_Union.device.sensor[16].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[16].data_firstaddress,
	&Device_RWReg_Union.device.sensor[16].data_quantity,
		&Device_RWReg_Union.device.sensor[17].sensor_number,
	&Device_RWReg_Union.device.sensor[17].sensor_address,
	&Device_RWReg_Union.device.sensor[17].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[17].data_firstaddress,
	&Device_RWReg_Union.device.sensor[17].data_quantity,
		&Device_RWReg_Union.device.sensor[18].sensor_number,
	&Device_RWReg_Union.device.sensor[18].sensor_address,
	&Device_RWReg_Union.device.sensor[18].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[18].data_firstaddress,
	&Device_RWReg_Union.device.sensor[18].data_quantity,
		&Device_RWReg_Union.device.sensor[19].sensor_number,
	&Device_RWReg_Union.device.sensor[19].sensor_address,
	&Device_RWReg_Union.device.sensor[19].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[19].data_firstaddress,
	&Device_RWReg_Union.device.sensor[19].data_quantity,
		&Device_RWReg_Union.device.sensor[20].sensor_number,
	&Device_RWReg_Union.device.sensor[20].sensor_address,
	&Device_RWReg_Union.device.sensor[20].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[20].data_firstaddress,
	&Device_RWReg_Union.device.sensor[20].data_quantity,
		&Device_RWReg_Union.device.sensor[21].sensor_number,
	&Device_RWReg_Union.device.sensor[21].sensor_address,
	&Device_RWReg_Union.device.sensor[21].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[21].data_firstaddress,
	&Device_RWReg_Union.device.sensor[21].data_quantity,
		&Device_RWReg_Union.device.sensor[22].sensor_number,
	&Device_RWReg_Union.device.sensor[22].sensor_address,
	&Device_RWReg_Union.device.sensor[22].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[22].data_firstaddress,
	&Device_RWReg_Union.device.sensor[22].data_quantity,
		&Device_RWReg_Union.device.sensor[23].sensor_number,
	&Device_RWReg_Union.device.sensor[23].sensor_address,
	&Device_RWReg_Union.device.sensor[23].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[23].data_firstaddress,
	&Device_RWReg_Union.device.sensor[23].data_quantity,
		&Device_RWReg_Union.device.sensor[24].sensor_number,
	&Device_RWReg_Union.device.sensor[24].sensor_address,
	&Device_RWReg_Union.device.sensor[24].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[24].data_firstaddress,
	&Device_RWReg_Union.device.sensor[24].data_quantity,
		&Device_RWReg_Union.device.sensor[25].sensor_number,
	&Device_RWReg_Union.device.sensor[25].sensor_address,
	&Device_RWReg_Union.device.sensor[25].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[25].data_firstaddress,
	&Device_RWReg_Union.device.sensor[25].data_quantity,
		&Device_RWReg_Union.device.sensor[26].sensor_number,
	&Device_RWReg_Union.device.sensor[26].sensor_address,
	&Device_RWReg_Union.device.sensor[26].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[26].data_firstaddress,
	&Device_RWReg_Union.device.sensor[26].data_quantity,
		&Device_RWReg_Union.device.sensor[27].sensor_number,
	&Device_RWReg_Union.device.sensor[27].sensor_address,
	&Device_RWReg_Union.device.sensor[27].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[27].data_firstaddress,
	&Device_RWReg_Union.device.sensor[27].data_quantity,
		&Device_RWReg_Union.device.sensor[28].sensor_number,
	&Device_RWReg_Union.device.sensor[28].sensor_address,
	&Device_RWReg_Union.device.sensor[28].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[28].data_firstaddress,
	&Device_RWReg_Union.device.sensor[28].data_quantity,
		&Device_RWReg_Union.device.sensor[29].sensor_number,
	&Device_RWReg_Union.device.sensor[29].sensor_address,
	&Device_RWReg_Union.device.sensor[29].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[29].data_firstaddress,
	&Device_RWReg_Union.device.sensor[29].data_quantity,
		&Device_RWReg_Union.device.sensor[30].sensor_number,
	&Device_RWReg_Union.device.sensor[30].sensor_address,
	&Device_RWReg_Union.device.sensor[30].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[30].data_firstaddress,
	&Device_RWReg_Union.device.sensor[30].data_quantity,
		&Device_RWReg_Union.device.sensor[31].sensor_number,
	&Device_RWReg_Union.device.sensor[31].sensor_address,
	&Device_RWReg_Union.device.sensor[31].sensor_serialnumber,
	&Device_RWReg_Union.device.sensor[31].data_firstaddress,
	&Device_RWReg_Union.device.sensor[31].data_quantity,

};

uint16_t* const Register43000[]=
{
	&Device_RWReg_Union.device.sensor[0].data[0],
	&Device_RWReg_Union.device.sensor[0].data[1],
	&Device_RWReg_Union.device.sensor[0].data[2],
	&Device_RWReg_Union.device.sensor[0].data[3],
		&Device_RWReg_Union.device.sensor[1].data[0],
	&Device_RWReg_Union.device.sensor[1].data[1],
	&Device_RWReg_Union.device.sensor[1].data[2],
	&Device_RWReg_Union.device.sensor[1].data[3],
		&Device_RWReg_Union.device.sensor[2].data[0],
	&Device_RWReg_Union.device.sensor[2].data[1],
	&Device_RWReg_Union.device.sensor[2].data[2],
	&Device_RWReg_Union.device.sensor[2].data[3],
		&Device_RWReg_Union.device.sensor[3].data[0],
	&Device_RWReg_Union.device.sensor[3].data[1],
	&Device_RWReg_Union.device.sensor[3].data[2],
	&Device_RWReg_Union.device.sensor[3].data[3],
		&Device_RWReg_Union.device.sensor[4].data[0],
	&Device_RWReg_Union.device.sensor[4].data[1],
	&Device_RWReg_Union.device.sensor[4].data[2],
	&Device_RWReg_Union.device.sensor[4].data[3],
		&Device_RWReg_Union.device.sensor[5].data[0],
	&Device_RWReg_Union.device.sensor[5].data[1],
	&Device_RWReg_Union.device.sensor[5].data[2],
	&Device_RWReg_Union.device.sensor[5].data[3],
		&Device_RWReg_Union.device.sensor[6].data[0],
	&Device_RWReg_Union.device.sensor[6].data[1],
	&Device_RWReg_Union.device.sensor[6].data[2],
	&Device_RWReg_Union.device.sensor[6].data[3],
		&Device_RWReg_Union.device.sensor[7].data[0],
	&Device_RWReg_Union.device.sensor[7].data[1],
	&Device_RWReg_Union.device.sensor[7].data[2],
	&Device_RWReg_Union.device.sensor[7].data[3],
		&Device_RWReg_Union.device.sensor[8].data[0],
	&Device_RWReg_Union.device.sensor[8].data[1],
	&Device_RWReg_Union.device.sensor[8].data[2],
	&Device_RWReg_Union.device.sensor[8].data[3],
		&Device_RWReg_Union.device.sensor[9].data[0],
	&Device_RWReg_Union.device.sensor[9].data[1],
	&Device_RWReg_Union.device.sensor[9].data[2],
	&Device_RWReg_Union.device.sensor[9].data[3],
		&Device_RWReg_Union.device.sensor[10].data[0],
	&Device_RWReg_Union.device.sensor[10].data[1],
	&Device_RWReg_Union.device.sensor[10].data[2],
	&Device_RWReg_Union.device.sensor[10].data[3],
		&Device_RWReg_Union.device.sensor[11].data[0],
	&Device_RWReg_Union.device.sensor[11].data[1],
	&Device_RWReg_Union.device.sensor[11].data[2],
	&Device_RWReg_Union.device.sensor[11].data[3],
		&Device_RWReg_Union.device.sensor[12].data[0],
	&Device_RWReg_Union.device.sensor[12].data[1],
	&Device_RWReg_Union.device.sensor[12].data[2],
	&Device_RWReg_Union.device.sensor[12].data[3],
		&Device_RWReg_Union.device.sensor[13].data[0],
	&Device_RWReg_Union.device.sensor[13].data[1],
	&Device_RWReg_Union.device.sensor[13].data[2],
	&Device_RWReg_Union.device.sensor[13].data[3],
		&Device_RWReg_Union.device.sensor[14].data[0],
	&Device_RWReg_Union.device.sensor[14].data[1],
	&Device_RWReg_Union.device.sensor[14].data[2],
	&Device_RWReg_Union.device.sensor[14].data[3],
		&Device_RWReg_Union.device.sensor[15].data[0],
	&Device_RWReg_Union.device.sensor[15].data[1],
	&Device_RWReg_Union.device.sensor[15].data[2],
	&Device_RWReg_Union.device.sensor[15].data[3],
		&Device_RWReg_Union.device.sensor[16].data[0],
	&Device_RWReg_Union.device.sensor[16].data[1],
	&Device_RWReg_Union.device.sensor[16].data[2],
	&Device_RWReg_Union.device.sensor[16].data[3],
		&Device_RWReg_Union.device.sensor[17].data[0],
	&Device_RWReg_Union.device.sensor[17].data[1],
	&Device_RWReg_Union.device.sensor[17].data[2],
	&Device_RWReg_Union.device.sensor[17].data[3],
		&Device_RWReg_Union.device.sensor[18].data[0],
	&Device_RWReg_Union.device.sensor[18].data[1],
	&Device_RWReg_Union.device.sensor[18].data[2],
	&Device_RWReg_Union.device.sensor[18].data[3],
		&Device_RWReg_Union.device.sensor[19].data[0],
	&Device_RWReg_Union.device.sensor[19].data[1],
	&Device_RWReg_Union.device.sensor[19].data[2],
	&Device_RWReg_Union.device.sensor[19].data[3],
		&Device_RWReg_Union.device.sensor[20].data[0],
	&Device_RWReg_Union.device.sensor[20].data[1],
	&Device_RWReg_Union.device.sensor[20].data[2],
	&Device_RWReg_Union.device.sensor[20].data[3],
		&Device_RWReg_Union.device.sensor[21].data[0],
	&Device_RWReg_Union.device.sensor[21].data[1],
	&Device_RWReg_Union.device.sensor[21].data[2],
	&Device_RWReg_Union.device.sensor[21].data[3],
		&Device_RWReg_Union.device.sensor[22].data[0],
	&Device_RWReg_Union.device.sensor[22].data[1],
	&Device_RWReg_Union.device.sensor[22].data[2],
	&Device_RWReg_Union.device.sensor[22].data[3],
		&Device_RWReg_Union.device.sensor[23].data[0],
	&Device_RWReg_Union.device.sensor[23].data[1],
	&Device_RWReg_Union.device.sensor[23].data[2],
	&Device_RWReg_Union.device.sensor[23].data[3],
		&Device_RWReg_Union.device.sensor[24].data[0],
	&Device_RWReg_Union.device.sensor[24].data[1],
	&Device_RWReg_Union.device.sensor[24].data[2],
	&Device_RWReg_Union.device.sensor[24].data[3],
		&Device_RWReg_Union.device.sensor[25].data[0],
	&Device_RWReg_Union.device.sensor[25].data[1],
	&Device_RWReg_Union.device.sensor[25].data[2],
	&Device_RWReg_Union.device.sensor[25].data[3],
		&Device_RWReg_Union.device.sensor[26].data[0],
	&Device_RWReg_Union.device.sensor[26].data[1],
	&Device_RWReg_Union.device.sensor[26].data[2],
	&Device_RWReg_Union.device.sensor[26].data[3],
		&Device_RWReg_Union.device.sensor[27].data[0],
	&Device_RWReg_Union.device.sensor[27].data[1],
	&Device_RWReg_Union.device.sensor[27].data[2],
	&Device_RWReg_Union.device.sensor[27].data[3],
		&Device_RWReg_Union.device.sensor[28].data[0],
	&Device_RWReg_Union.device.sensor[28].data[1],
	&Device_RWReg_Union.device.sensor[28].data[2],
	&Device_RWReg_Union.device.sensor[28].data[3],
		&Device_RWReg_Union.device.sensor[29].data[0],
	&Device_RWReg_Union.device.sensor[29].data[1],
	&Device_RWReg_Union.device.sensor[29].data[2],
	&Device_RWReg_Union.device.sensor[29].data[3],
		&Device_RWReg_Union.device.sensor[30].data[0],
	&Device_RWReg_Union.device.sensor[30].data[1],
	&Device_RWReg_Union.device.sensor[30].data[2],
	&Device_RWReg_Union.device.sensor[30].data[3],
			&Device_RWReg_Union.device.sensor[31].data[0],
	&Device_RWReg_Union.device.sensor[31].data[1],
	&Device_RWReg_Union.device.sensor[31].data[2],
	&Device_RWReg_Union.device.sensor[31].data[3],
		&Device_RWReg_Union.device.sensor[0].data_reg_address,
	&Device_RWReg_Union.device.sensor[0].sensor_state,
		&Device_RWReg_Union.device.sensor[1].data_reg_address,
	&Device_RWReg_Union.device.sensor[1].sensor_state,
		&Device_RWReg_Union.device.sensor[2].data_reg_address,
	&Device_RWReg_Union.device.sensor[2].sensor_state,
		&Device_RWReg_Union.device.sensor[3].data_reg_address,
	&Device_RWReg_Union.device.sensor[3].sensor_state,
		&Device_RWReg_Union.device.sensor[4].data_reg_address,
	&Device_RWReg_Union.device.sensor[4].sensor_state,
		&Device_RWReg_Union.device.sensor[5].data_reg_address,
	&Device_RWReg_Union.device.sensor[5].sensor_state,
		&Device_RWReg_Union.device.sensor[6].data_reg_address,
	&Device_RWReg_Union.device.sensor[6].sensor_state,
		&Device_RWReg_Union.device.sensor[7].data_reg_address,
	&Device_RWReg_Union.device.sensor[7].sensor_state,
	
		&Device_RWReg_Union.device.sensor[8].data_reg_address,
	&Device_RWReg_Union.device.sensor[8].sensor_state,
	
		&Device_RWReg_Union.device.sensor[9].data_reg_address,
	&Device_RWReg_Union.device.sensor[9].sensor_state,
	
		&Device_RWReg_Union.device.sensor[10].data_reg_address,
	&Device_RWReg_Union.device.sensor[10].sensor_state,
	
		&Device_RWReg_Union.device.sensor[11].data_reg_address,
	&Device_RWReg_Union.device.sensor[11].sensor_state,
		&Device_RWReg_Union.device.sensor[12].data_reg_address,
	&Device_RWReg_Union.device.sensor[12].sensor_state,
	
		&Device_RWReg_Union.device.sensor[13].data_reg_address,
	&Device_RWReg_Union.device.sensor[13].sensor_state,
		&Device_RWReg_Union.device.sensor[14].data_reg_address,
	&Device_RWReg_Union.device.sensor[14].sensor_state,
		&Device_RWReg_Union.device.sensor[15].data_reg_address,
	&Device_RWReg_Union.device.sensor[15].sensor_state,
		&Device_RWReg_Union.device.sensor[15].data_reg_address,
	&Device_RWReg_Union.device.sensor[15].sensor_state,
		&Device_RWReg_Union.device.sensor[16].data_reg_address,
	&Device_RWReg_Union.device.sensor[16].sensor_state,
		&Device_RWReg_Union.device.sensor[17].data_reg_address,
	&Device_RWReg_Union.device.sensor[17].sensor_state,
		&Device_RWReg_Union.device.sensor[18].data_reg_address,
	&Device_RWReg_Union.device.sensor[18].sensor_state,
	
		&Device_RWReg_Union.device.sensor[19].data_reg_address,
	&Device_RWReg_Union.device.sensor[19].sensor_state,
		&Device_RWReg_Union.device.sensor[20].data_reg_address,
	&Device_RWReg_Union.device.sensor[20].sensor_state,
		&Device_RWReg_Union.device.sensor[21].data_reg_address,
	&Device_RWReg_Union.device.sensor[21].sensor_state,
		&Device_RWReg_Union.device.sensor[22].data_reg_address,
	&Device_RWReg_Union.device.sensor[22].sensor_state,
		&Device_RWReg_Union.device.sensor[23].data_reg_address,
	&Device_RWReg_Union.device.sensor[23].sensor_state,
		&Device_RWReg_Union.device.sensor[24].data_reg_address,
	&Device_RWReg_Union.device.sensor[24].sensor_state,
		&Device_RWReg_Union.device.sensor[25].data_reg_address,
	&Device_RWReg_Union.device.sensor[25].sensor_state,
		&Device_RWReg_Union.device.sensor[26].data_reg_address,
	&Device_RWReg_Union.device.sensor[26].sensor_state,
		&Device_RWReg_Union.device.sensor[27].data_reg_address,
	&Device_RWReg_Union.device.sensor[27].sensor_state,
		&Device_RWReg_Union.device.sensor[28].data_reg_address,
	&Device_RWReg_Union.device.sensor[28].sensor_state,
		&Device_RWReg_Union.device.sensor[29].data_reg_address,
	&Device_RWReg_Union.device.sensor[29].sensor_state,
		&Device_RWReg_Union.device.sensor[30].data_reg_address,
	&Device_RWReg_Union.device.sensor[30].sensor_state,
		&Device_RWReg_Union.device.sensor[31].data_reg_address,
	&Device_RWReg_Union.device.sensor[31].sensor_state
	
	
	

};


uint16_t* const Register44000[]=
{
	&Device_RWReg_Union.device.Address_ACU,
	&Device_RWReg_Union.device.SensorTotalNum,
	&Device_RWReg_Union.device.WorkMod,
	&Device_RWReg_Union.device.UploadPeriod,
	&Device_RWReg_Union.device.RS485_Sensor_Baud,
	&Device_RWReg_Union.device.RS485_Extend_Baud,
	&Device_RWReg_Union.device.Address_ExternRS485,
	&Device_RWReg_Union.device.RS485_4G_Baud
	
};

uint16_t RegisterMap_ReadData(uint16_t index)
{
	if(index>=41000 && index<42000)
	{
		return *(Register41000[index-41000]);
	}
	else if(index>=42000 && index<43000)
	{
		return *(Register42000[index-42000]);
	}
	else if(index>=43000 && index<44000)
	{
		return *(Register43000[index-43000]);
	}
	else if(index>=44000 && index<45000)
	{
		return *(Register44000[index-44000]);
	}
	else 
	{
		return 65534;
	}
	
}
void RegisterMap_WriteData(uint16_t index, uint16_t data)
{

	if(index>=41000 && index<42000)
	{
		*(Register41000[index-41000]) = data;
	}
	else if(index>=42000 && index<43000)
	{
		*(Register42000[index-42000]) = data;
	}
	else if(index>=43000 && index<44000)
	{
		*(Register43000[index-43000]) = data;
	}
		else if(index>=44000 && index<45000)
	{
		*(Register44000[index-44000]) = data;
		if((index-44000) == 4)  //改变波特率
		{
			USART2_Config(BAUDtable[data]); 
		}
		if((index-44000) == 5)  //改变波特率
		{
			UART4_Config(BAUDtable[data]); 
		}
		if((index-44000) == 7)  //改变波特率
		{
			//USART2_Config(BAUDtable[data]); 
		}
	}
	else 
	{
		return;
	}

}

//只读整型   8个 地址30000  (OK)
 u16   ROdat[8]   = {20,20,20,20,10,10,10,10}; 	 	
 
//可读可写整型   8个  地址40000 (OK)
 u16   RWdat[8]   = {1,1,1,1,0,0,0,0}; 	 	
 u16   RWReg[1290];
 
 u8 System_State=0;//四个灯，低4位
 u8 Relay_State=0;
 u16 InputData=0;
 u8 SensorLeaveFlag=0;
 
 
 
 //浮点型
 float  temp0      = 1.15; //3F 93 33 33 				
 float  temp1      = 1.25; //3F A0 00 00 
 float  temp2      = 1.35; //3F AC CC CD  
 float  temp3      = 1.45; //3F B9 99 9A  
 float  temp4      = 1.55; //3F C6 66 66 
 float  temp5      = 1.65; //3F D3 33 33  
 float  temp6      = 1.75; //3F E0 00 00  
 float  temp7      = 1.85; //3F EC CC CD  
 
 //long型   8个
 long   adc0       = 789650; //			
 long   adc1       = 789651; //
 long   adc2       = 789652; //
 long   adc3       = 789653; //
 long   adc4       = 789654; //
 long   adc5       = 789655; //
 long   adc6       = 789656; //
 long   adc7       = 789657; //
 
//只读线圈   8个 地址10000 (OK)
 u8    ROstatus0  = 0;                 
 u8    ROstatus1  = 0;
 u8    ROstatus2  = 0;                 
 u8    ROstatus3  = 0; 
 u8    ROstatus4  = 0;                 
 u8    ROstatus5  = 0; 
 u8    ROstatus6  = 0;                 
 u8    ROstatus7  = 0; 
 
//可读可写线圈   8个 地址0 (OK)
 u8    RWstatus0  = 0;                 
 u8    RWstatus1  = 0;                 
 u8    RWstatus2  = 0;                 
 u8    RWstatus3  = 0; 
 u8    RWstatus4  = 0;                 
 u8    RWstatus5  = 0; 
 u8    RWstatus6  = 0;                 
 u8    RWstatus7  = 0; 
 
 
//4位char 数据转换为浮点与长整形数据
union 
{
	unsigned char uc[4];
	float fda; 
	long lda;
}un_4b;
 
//浮点型转换为整形
union
{
	u16 x[2];
	float y;
}ftemp;

//长整形转换为整形
union ul
{
	u16 x[2];
	long y;
}ltemp;

//字节数据转换为浮点数据
float BtoF(unsigned char *p) 
{ 
    float real;
	
    /*			
		un_4b.uc[0]=*(p+3); 
		un_4b.uc[1]=*(p+2); 
		un_4b.uc[2]=*(p+1); 
		un_4b.uc[3]=*p;
    */
	
    un_4b.uc[0]=*p; 
    un_4b.uc[1]=*(p+1); 
    un_4b.uc[2]=*(p+2); 
    un_4b.uc[3]=*(p+3); 
    real=un_4b.fda; 
	return 	real;
}

//字节数据转换为整形数据
long BtoL(unsigned char *p) 
{ 
    long real;
	
    /*			
		un_4b.uc[0]=*(p+3); 
		un_4b.uc[1]=*(p+2); 
		un_4b.uc[2]=*(p+1); 
		un_4b.uc[3]=*p; 
    */
	
    un_4b.uc[0]=*p; 
    un_4b.uc[1]=*(p+1); 
    un_4b.uc[2]=*(p+2); 
    un_4b.uc[3]=*(p+3); 
    real=un_4b.lda; 
	return 	real;
}


/**
 * 函数名：getCoilVal
 * 描述  ：读取线圈状态
 * 输入  ：无
 * 输出  ：返回0表示成功
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
u16 getCoilVal(u16 addr,u16 *tempData)
{
	u16 tempAddr;
	tempAddr = addr;//只取低8位地址
	
	switch(tempAddr)
	{
		/*
			读取 （可读可写） 线圈.
			如果RWstatus0是IO口则。
			if（RWstatus0 == 0）
			*tempData |= 0x01;
			else
			*tempData &= 0xfe;
		*/
		case RWSTATUES0:   *tempData = RWstatus0; break;
		case RWSTATUES1:   *tempData = RWstatus1; break;
		case RWSTATUES2:   *tempData = RWstatus2; break;
		case RWSTATUES3:   *tempData = RWstatus3; break;
		case RWSTATUES4:   *tempData = RWstatus4; break;
		case RWSTATUES5:   *tempData = RWstatus5; break;
		case RWSTATUES6:   *tempData = RWstatus6; break;
		case RWSTATUES7:   *tempData = RWstatus7; break;
		
		/*读取 （只读） 线圈*/
		case ROSTATUES0:   *tempData = PDin(4); break;  
		case ROSTATUES1:   *tempData = PDin(5); break;
		case ROSTATUES2:   *tempData = PDin(6); break;  
		case ROSTATUES3:   *tempData = PDin(7); break; 
		case ROSTATUES4:   *tempData = ROstatus4; break;  
		case ROSTATUES5:   *tempData = ROstatus5; break; 
		case ROSTATUES6:   *tempData = ROstatus6; break;  
		case ROSTATUES7:   *tempData = ROstatus7; break; 
		
		default:  break;       
	} 
	return  0;
}

/**
 * 函数名：setCoilVal
 * 描述  ：设置线圈状态
 * 输入  ：无
 * 输出  ：返回0表示成功
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
u16 setCoilVal(u16 addr,u16 tempData)
{
	u16 tempAddr;
	tempAddr = addr;//只取低8位地址
	
	Device_RWReg_Union.device.relay[addr].state = (tempData & 0x0001);
	
	switch(tempAddr)
	{
		/*
			设置 （可读可写） 线圈
			如果RWstatus0是IO口则。
			if(tempData == 1)
		    RWstatus0 = 0;
			else
			RWstatus0 = 1;
		*/
		/*
		case RWSTATUES0:   RWstatus0 = tempData; break;
		case RWSTATUES1:   RWstatus1 = tempData; break;
		case RWSTATUES2:   RWstatus2 = tempData; break;
		case RWSTATUES3:   RWstatus3 = tempData; break;
		case RWSTATUES4:   RWstatus4 = tempData; break;
		case RWSTATUES5:   RWstatus5 = tempData; break;
		case RWSTATUES6:   RWstatus6 = tempData; break;
		case RWSTATUES7:   RWstatus7 = tempData; break;
		*/
		
		/*设置 （只读） 线圈*/
//		case ROSTATUES0:   ROstatus0 = tempData; break;  
//		case ROSTATUES1:   ROstatus1 = tempData; break;
//		case ROSTATUES2:   ROstatus2 = tempData; break;  
//		case ROSTATUES3:   ROstatus3 = tempData; break;
//		case ROSTATUES4:   ROstatus4 = tempData; break;  
//		case ROSTATUES5:   ROstatus5 = tempData; break;
//		case ROSTATUES6:   ROstatus6 = tempData; break;  
//		case ROSTATUES7:   ROstatus7 = tempData; break;
		
		//
		default:  break;   
	} 
	return 0;
}
	

/**
 * 函数名：getRegisterVal
 * 描述  ：读取寄存器内容函数
 * 输入  ：无
 * 输出  ：返回0表示成功
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
u16 getRegisterVal(u16 addr,u16 *tempData)
{
	//支持整型
	if(addr<ResisterAddressMax)
	{
		*tempData=RWReg[addr];
	}
	
	/*
	
	switch(addr)								 
	{
		//读取 （只读） 整形变量 30000
		case RODAT0: { *tempData = ROdat[0]; break; }
		case RODAT1: { *tempData = ROdat[1]; break; }
		case RODAT2: { *tempData = ROdat[2]; break; }
		case RODAT3: { *tempData = ROdat[3]; break; }
		case RODAT4: { *tempData = ROdat[4]; break; }
		case RODAT5: { *tempData = ROdat[5]; break; }
		case RODAT6: { *tempData = ROdat[6]; break; }
		case RODAT7: { *tempData = ROdat[7]; break; }
		
		//读取 （可读可写） 整形变量 40000
		case RWDAT0: { *tempData = RWdat[0]; break; }
		case RWDAT1: { *tempData = RWdat[1]; break; }
		case RWDAT2: { *tempData = RWdat[2]; break; }
		case RWDAT3: { *tempData = RWdat[3]; break; } 
		case RWDAT4: { *tempData = RWdat[4]; break; }
		case RWDAT5: { *tempData = RWdat[5]; break; }
		case RWDAT6: { *tempData = RWdat[6]; break; }
		case RWDAT7: { *tempData = RWdat[7]; break; } 
		
		//读取 （浮点型） 变量
		case TEMP0:   { ftemp.y   = temp0 , *tempData = ftemp.x[0];   break; }
		case TEMP0+1: { *tempData = ftemp.x[1];   break; } 
		case TEMP1:   { ftemp.y   = temp1 , *tempData = ftemp.x[0];   break; }
		case TEMP1+1: { *tempData = ftemp.x[1];   break; }
		case TEMP2:   { ftemp.y   = temp2 , *tempData = ftemp.x[0];   break; }
		case TEMP2+1: { *tempData = ftemp.x[1];   break; }
		case TEMP3:   { ftemp.y   = temp3 , *tempData = ftemp.x[0];   break; }
		case TEMP3+1: { *tempData = ftemp.x[1];   break; }
		case TEMP4:   { ftemp.y   = temp4 , *tempData = ftemp.x[0];   break; }
		case TEMP4+1: { *tempData = ftemp.x[1];   break; }
		case TEMP5:   { ftemp.y   = temp5 , *tempData = ftemp.x[0];   break; }
		case TEMP5+1: { *tempData = ftemp.x[1];   break; }
		case TEMP6:   { ftemp.y   = temp6 , *tempData = ftemp.x[0];   break; }
		case TEMP6+1: { *tempData = ftemp.x[1];   break; }
		case TEMP7:   { ftemp.y   = temp7 , *tempData = ftemp.x[0];   break; }
		case TEMP7+1: { *tempData = ftemp.x[1];   break; }
		
		//读取（长整形） 变量
		case ADC00:    {  ltemp.y  = adc0 , *tempData = ltemp.x[0];   break; } 
		case ADC00+1:  { *tempData = ltemp.x[1];   break; }
		case ADC11:    {  ltemp.y  = adc1 , *tempData = ltemp.x[0];   break; } 
		case ADC11+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC22:    {  ltemp.y  = adc2 , *tempData = ltemp.x[0];   break; } 
		case ADC22+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC33:    {  ltemp.y  = adc3 , *tempData = ltemp.x[0];   break; } 
		case ADC33+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC44:    {  ltemp.y  = adc4 , *tempData = ltemp.x[0];   break; } 
		case ADC44+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC55:    {  ltemp.y  = adc5 , *tempData = ltemp.x[0];   break; } 
		case ADC55+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC66:    {  ltemp.y  = adc6 , *tempData = ltemp.x[0];   break; } 
		case ADC66+1:  { *tempData = ltemp.x[1];   break; } 
		case ADC77:    {  ltemp.y  = adc7 , *tempData = ltemp.x[0];   break; } 
		case ADC77+1:  { *tempData = ltemp.x[1];   break; } 
		
		//
		default:  break;  
	}
	*/
	return 0;
}


/**
 * 函数名：setRegisterVal
 * 描述  ：设置寄存器内容函数
 * 输入  ：无
 * 输出  ：返回0表示成功
 * 调用  ：外部调用
 * 作者  :YaoTong 2017
 */
u16 setRegisterVal(u16 addr,u16 tempData)
{
	
	
		if(addr<ResisterAddressMax)
	{
		RWReg[addr]=tempData;
	}
	/*
	switch(addr)
	{
		//设置 （只读） 寄存器
//		case RODAT0: { ROdat[0]  = tempData ; break; }
//		case RODAT1: { ROdat[1]  = tempData ; break; }
//		case RODAT2: { ROdat[2]  = tempData ; break; }
//		case RODAT3: { ROdat[3]  = tempData ; break; }
//		case RODAT4: { ROdat[4]  = tempData ; break; }
//		case RODAT5: { ROdat[5]  = tempData ; break; }
//		case RODAT6: { ROdat[6]  = tempData ; break; }
//		case RODAT7: { ROdat[7]  = tempData ; break; }
		
		//设置 （可读可写） 寄存器
		case RWDAT0: { RWdat[0]  = tempData ; break; }  
		case RWDAT1: { RWdat[1]  = tempData ; break; }  
		case RWDAT2: { RWdat[2]  = tempData ; break; }  
		case RWDAT3: { RWdat[3]  = tempData ; break; }
		case RWDAT4: { RWdat[4]  = tempData ; break; }  
		case RWDAT5: { RWdat[5]  = tempData ; break; }  
		case RWDAT6: { RWdat[6]  = tempData ; break; }  
		case RWDAT7: { RWdat[7]  = tempData ; break; }
		
		//设置 （浮点型） 寄存器
		case TEMP0:   { ftemp.x[0] = tempData; break; }
		case TEMP0+1: { ftemp.x[1] = tempData; temp0 = ftemp.y; break; }
		case TEMP1:   { ftemp.x[0] = tempData; break; }
		case TEMP1+1: { ftemp.x[1] = tempData; temp1 = ftemp.y; break; }
		case TEMP2:   { ftemp.x[0] = tempData; break; }
		case TEMP2+1: { ftemp.x[1] = tempData; temp2 = ftemp.y; break; }
		case TEMP3:   { ftemp.x[0] = tempData; break; }
		case TEMP3+1: { ftemp.x[1] = tempData; temp3 = ftemp.y; break; }
		case TEMP4:   { ftemp.x[0] = tempData; break; }
		case TEMP4+1: { ftemp.x[1] = tempData; temp4 = ftemp.y; break; }
		case TEMP5:   { ftemp.x[0] = tempData; break; }
		case TEMP5+1: { ftemp.x[1] = tempData; temp5 = ftemp.y; break; }
		case TEMP6:   { ftemp.x[0] = tempData; break; }
		case TEMP6+1: { ftemp.x[1] = tempData; temp6 = ftemp.y; break; }
		case TEMP7:   { ftemp.x[0] = tempData; break; }
		case TEMP7+1: { ftemp.x[1] = tempData; temp7 = ftemp.y; break; }
		
		//设置 （长整形） 寄存器
		case ADC00:    { ltemp.x[0] = tempData; break; } 
		case ADC00+1:  { ltemp.x[1] = tempData; adc0 = ftemp.y; break; }
		case ADC11:    { ltemp.x[0] = tempData; break; } 
		case ADC11+1:  { ltemp.x[1] = tempData; adc1 = ftemp.y; break; } 
		case ADC22:    { ltemp.x[0] = tempData; break; } 
		case ADC22+1:  { ltemp.x[1] = tempData; adc2 = ftemp.y; break; } 
		case ADC33:    { ltemp.x[0] = tempData; break; } 
		case ADC33+1:  { ltemp.x[1] = tempData; adc3 = ftemp.y; break; } 
		case ADC44:    { ltemp.x[0] = tempData; break; } 
		case ADC44+1:  { ltemp.x[1] = tempData; adc4 = ftemp.y; break; } 
		case ADC55:    { ltemp.x[0] = tempData; break; } 
		case ADC55+1:  { ltemp.x[1] = tempData; adc5 = ftemp.y; break; } 
		case ADC66:    { ltemp.x[0] = tempData; break; } 
		case ADC66+1:  { ltemp.x[1] = tempData; adc6 = ftemp.y; break; } 
		case ADC77:    { ltemp.x[0] = tempData; break; } 
		case ADC77+1:  { ltemp.x[1] = tempData; adc7 = ftemp.y; break; } 
		
		//
		default:  break;  
	}*/
	return 0;
}




