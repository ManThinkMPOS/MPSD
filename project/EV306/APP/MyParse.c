#include "Global.h"
#include "include.h"
#include "MyAPP.h"
#include "MyBoard.h"
#include "MyGlobal.h"
#include "MyParse.h" 

/********************************************************
* Function for Deal PDA data 
*
********************************************************/
void MT_SW_Process(u1_t *buf,u1_t lenth,u1_t port) 
{ 
  
}
/********************************************************
* Function for Deal downlink data 
*
********************************************************/
void MT_DN_Process(u1_t *buf,u1_t lenth,u1_t port) 
{ 
    u2_t interval;
    u1_t para_buffer[8];
    for(u1_t i=0;i<8;i++){ para_buffer[i] = appPara.ByteS[i];}
    if(port != SENSOR_PORT) return;
    if(lenth!=7) return;
    if(buf[0]!=0xA1) return;
    if((buf[1]!=0x08)||(buf[2]!=0x04)) return;
    interval = (buf[6]<<8)+buf[5];
    if((interval==0xFFFF)||(interval==0x0)){mpos_osfun.Task_Remove(&MT_TaskSensorTx);interval=0;} //stop
    else if(interval>0x05A0) interval = MT_TaskSensorTx.interval/60000;  //deal nothing
    else mpos_osfun.Task_SetPeriod(&MT_TaskSensorTx,interval*60000); 
    para_buffer[5] = (u1_t)interval;
    para_buffer[6] = (u1_t)(interval>>8);
    mpos_lws.paraAPPSave(para_buffer,8);
    MT_MyParaInit();
}