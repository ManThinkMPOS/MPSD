/*******************************************************************************
 * Copyright (c) ManThink Technology Ltd. co.
 * All rights reserved. This program and the accompanying materials
 * are made available under the software of IAR for ARM version 7.60.2
 * This is a demo working with the SDK of LWS made by ManThink Technology
 * LWS is a SDK for OM 801 which realize LoRaWAN function.
 * The Demo should be run on the hardware of OM801 produced by ManThink Technology
 * http://www.manthink.cn 
 * contact info : info@manthink.cn
 * contributor  : mingfei zhao
 *******************************************************************************/
#include "MP_OS.h"
#include "string.h"
#include "Global.h"
#include "MyGlobal.h"

void MT_MyInit (void) __attribute__((section(".ARM.__at_0x0000ecd0")));
void MT_MyInit()
{
	mpos_osfun.SysParaInit(); //parameters in flash.
	MT_MyHookInit();             //Upload the hook function
        MT_MyParaInit();             //Initial the userdata
	MT_MyBoardInit();            //Initial the hardware
	MT_LoRaWANParaInitial();   //user's intialization
	mpos_driver.kickdog();    //kick watch dog
	mpos_lws.LWS_init();      //intialization of LoRaWAN SDK
	mpos_driver.kickdog();    //kick watch dog
	mpos_lws.LoRaWANInit();   //Initial the LoRaWAN patameter 
        MT_SetupSensorTxTask();      //Set the peridic task
        MT_SetupOnceEventTask();     //Set the once event task        
}
void mpos_main (void) __attribute__((section(".ARM.__at_0x0000ec00")));
void  mpos_main() //@".mposinit"
{
	#if _DEBUGING
	StackFunction.watchdog=false;StackFunction.nosleep=true; 
	#else
	StackFunction.watchdog=true;StackFunction.nosleep=false; 
	#endif
	StackFunction.uart1=true;
	StackFunction.lorawan=true; StackFunction.FlashBackup=true;
	StackFunction.MTprotocol=true;
        mpos_driver.Clock_Init();
	mp_userInit=MT_MyInit;
}
/*
  MPOS second development demo
1.LoRaWAN Stack library£º LWS417Alib.a
  The library realise most functions of LoRaWAN stack and provide some interfaces function for users.
2.MyAPP.c  
  The file is used to define some functions of user and setup periodic task and once event task.
3.MyApp_INT.c  
  The file is used to define all the interrupts of MPOS.
4.MyApp_LWS.c  
  The file is used to initial the LoRaWAN parameter and handling events of LoRaWAN stack.
5.My Board.c  
  The file is used to initial the OMX02 havdwares used by users.
6.MyParse.c  
  The file is used to define the analytic functions of users.
7.MyTask.c  
  The file is used to define periodic task and once event task
8.MyType.h  
  The file is used to define the types of variables.
9.MyGlobal.c 
  The file is used to define the global variables.
10.mymain.c 
  The file is used to initial the LoRaWAN stack and some global configurations.
*/
