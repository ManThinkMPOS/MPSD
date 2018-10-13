#ifndef _MY_GLOBAL_H
#define _MY_GLOBAL_H
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
#include "string.h"
#include "MyAPP.h"
#include "MyBoard.h"
#include "MyTask.h"
#include "MyAPP.h"
#include "MyApp_INT.h"
#include "MyApp_LWS.h"
#include "MyType.h"
#include "SHT20.h"
#include "DS18B20.h"
#include "LIS2DH12.h"
#include "MyParse.h"

//define variable of user
#define SENSOR_PORT          0x0B
#define INFOR_LEN            20

extern S_periodTask MT_TaskSensorTx ;
extern U_MT_SensorPARA MT_Sensor;
extern MT_Sensor_InfoPara  *MT_Sensor_AppPara;
extern bool mt_dtu_resetAfterLWT;

#endif