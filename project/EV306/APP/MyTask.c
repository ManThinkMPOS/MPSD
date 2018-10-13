#include "MKL17Z644.h"
#include "Global.h"
#include "include.h"
#include "MyGlobal.h"
/********************************************************
* Function: Periodic function for tx sensor data 
********************************************************/
void MT_SensorTx(void * task,void *p)
{
  MT_AUX_LED_ON();             //LED ON                                                                    
  MT_Sensor.MPRegister.AlarmStatus.Bits.Sht20Status = ~SHT2x_MeasureTH(&MT_Sensor.MPRegister.Sht20Temp[0]);  //Test temperature and humidity by SHT20 uint:¡æ & %RH 
  MT_Sensor.MPRegister.AlarmStatus.Bits.Ds18b20Status = ~DS18B20_ReadTemp(&MT_Sensor.MPRegister.Ds18b20Temp); //Test temperature  by DS18B20 uint:¡æ
  LIS2DH12_ReadXYZACC(MT_Sensor.MPRegister.ACC_X);  
  MT_Sensor.MPRegister.Vol = (uint8_t)((5.118*RunStatus.Varible.BattLevel)/100+20);                 //Test voltage by MCU uint:100mV
  MT_Sensor.MPRegister.RSSI = RunStatus.Varible.RSSI;                                               //The signal RSSI of module
  MT_Sensor.MPRegister.SNR = RunStatus.Varible.SNR;                                                 //The signal SNR of module                                             //Test 3 axis acceleration by LIS2DH12
  mpos_lws.LW_TxData((unsigned char*)(MT_Sensor.Bytes),INFOR_LEN,SENSOR_PORT, LWOP_LTC);   
}

/********************************************************
* Function: key tigger to TX Data(SetupOnceEventTask)
********************************************************/
void MT_Tx_Data()
{
  MT_AUX_LED_ON();   
  mpos_lws.LW_TxData((unsigned char*)(MT_Sensor.Bytes),INFOR_LEN,SENSOR_PORT, LWOP_LTC);     
}