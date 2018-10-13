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
	//LoRaWANParaInitial();   //user's intialization
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
