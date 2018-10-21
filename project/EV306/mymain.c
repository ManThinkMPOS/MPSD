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
	mpos_osfun.SysParaInit(); //Inital the parameters,read para in flash and upload them into systerm para.
	MT_MyHookInit();          //Upload the hook function
        MT_MyParaInit();          //Initial the userdata
	MT_MyBoardInit();         //Initial the user's hardware 
	MT_LoRaWANParaInitial();  //Initial LoRaWAN parameter
	mpos_driver.kickdog();    //Kick watch dog
	mpos_lws.LWS_init();      //Intialization of LoRaWAN SDK
	mpos_driver.kickdog();    //Kick watch dog
	mpos_lws.LoRaWANInit();   //Upload the LoRaWAN para into systerm 
        MT_SetupSensorTxTask();   //Set the peridic task
        MT_SetupOnceEventTask();  //Set the once event task        
}
void mpos_main (void) __attribute__((section(".ARM.__at_0x0000ec00")));
void  mpos_main() //@".mposinit"
{
	#if _DEBUGING                  //Disablel watchdog and sleep used for debug
	StackFunction.watchdog=false;StackFunction.nosleep=true; 
	#else                          //ENablel watchdog and sleep used for product running                                                           
	StackFunction.watchdog=true;StackFunction.nosleep=false; 
	#endif
	StackFunction.uart1=true;      //Enable UART1 function provide by MPOS
	StackFunction.lorawan=true;    //Enable LoRaWAN function of MPOS
        StackFunction.FlashBackup=true;//Enable backup of data store in flash
	StackFunction.MTprotocol=true; //Enable ManThink UART protocol e.g. 0XFF 0XAA... 
        mpos_driver.Clock_Init();      //Initial clock of the systerm
	mp_userInit=MT_MyInit;         //Iintial function of user
}
