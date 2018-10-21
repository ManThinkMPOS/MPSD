#include "MKL17Z644.h"
#include "Global.h"
#include "include.h"
#include "MyGlobal.h"
#include <stdlib.h>

/********************************************************
* Function for Flash_InitPara 
********************************************************/
void MT_SetupSensorTxTask()
{
     MT_TaskSensorTx.Task=MT_SensorTx;   //Set a periodic task
     MT_TaskSensorTx.interval = mpos_osfun.os_rlsbf2(MT_Sensor_AppPara->UpInterval)*60000;//Set execution cycle unit:ms
     MT_TaskSensorTx.cycles=0xFFFFFFFF;  //Set the execute times, if the value is 0xFFFFFFFF,it's infinite loop. 
     mpos_osfun.Task_Setup(&MT_TaskSensorTx);
}
void MT_SetupOnceEventTask()
{
  LPInfo.wakingBit.Bits.OnceEvent1=0;
  HookExcuteOnce1 = MT_Tx_Data; 
  LPInfo.wakingBit.Bits.OnceEvent2=1;
  HookExcuteOnce2 = MT_Join_Net;
}
void MT_app_HookAPPParaChanged(u1_t * paras)
{
  mt_dtu_resetAfterLWT=true;
}
void MT_MyHookInit()
{
  //HOOK_EXTI3_IRQHandler=MT_app_EXTI3_IRQHandler;
  //HOOK_EXTIWK_IRQHandler=MT_app_EXTIWK_IRQHandler;
  HOOK_EXTIPORTBCDE_WKIRQHandler=MT_app_WKIRQ;
  HOOK_EXTIPORTBCDE_GNIRQHandler=MT_app_GNIRQ;
  //HOOK_USART1_IRQHandler=MT_app_USART1_IRQHandler;
  HOOK_USART2_IRQHandler=MT_app_USART2_IRQHandler;
  Hook_Event.function=MT_HookUserEvent; // Event of LoRaWAN
  HookAPPParaChanged = MT_app_HookAPPParaChanged;
}

void MT_GetAppPara()
{
  mpos_lws.paraAPPGet((u1_t *)&appPara.paras,198);
  MT_Sensor_AppPara=(MT_Sensor_InfoPara *)appPara.paras.userPara;
}

void MT_MyParaInit()
{
      MT_GetAppPara();
      MT_Sensor.MPRegister.Command=0x21;
      MT_Sensor.MPRegister.InforFormat=0x08;
      MT_Sensor.MPRegister.MType=MT_Sensor_AppPara->MType;;
      MT_Sensor.MPRegister.HwVersion=MT_Sensor_AppPara->Hwversion; 
      MT_Sensor.MPRegister.FmVersion=MT_Sensor_AppPara->Fmversion;
      MT_Sensor.MPRegister.AlarmStatus.Bits.Sht20Status=0;
      MT_Sensor.MPRegister.AlarmStatus.Bits.Ds18b20Status=0;
      MT_Sensor.MPRegister.AlarmStatus.Bits.AccStatus=0;
      MT_Sensor.MPRegister.Sht20Temp[0]=25;
      MT_Sensor.MPRegister.Sht20Temp[1]=0;
      MT_Sensor.MPRegister.Sht20Hum[0]=50;
      MT_Sensor.MPRegister.Sht20Hum[1]=0;
      MT_Sensor.MPRegister.Ds18b20Temp=25;
      MT_Sensor.MPRegister.Vol=33;
      MT_Sensor.MPRegister.RSSI=0;
      MT_Sensor.MPRegister.SNR=0;      
}
