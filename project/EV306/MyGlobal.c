#include "MP_OS.h"
#include "Global.h"
#include "MyType.h"
U_MT_SensorPARA MT_Sensor;
S_periodTask MT_TaskSensorTx;
MT_Sensor_InfoPara  *MT_Sensor_AppPara;
bool mt_dtu_resetAfterLWT=false;