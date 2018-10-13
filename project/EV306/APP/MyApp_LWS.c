/*******************************************************************************
* Copyright (c) ManThink Technology Ltd. co.
* All rights reserved. This program and the accompanying materials
* are made available under the software of IAR for ARM version 7.60.2
* This is a demo working with the SDK of LWS made by ManThink Technology
* LWS is a SDK for OM402/OM802 which realize LoRaWAN function.
* The Demo should be run on the hardware of OM402/OM802 produced by ManThink Technology
* http://www.manthink.cn 
* contact info : info@manthink.cn
* contributor  : mingfei zhao
*******************************************************************************/
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
#include "string.h"
#include "MyGlobal.h"
/**********************Initialization of LoRaWAN******************************************************************/
void MT_LoRaWANParaInitial()
{
  //RunStatus.Varible.State.Bits.JoinStatus=0;
  //RunStatus.Varible.State.Bits.Mode=1;// classA
  //RunStatus.Varible.State.Bits.ADR=1;
  //RunStatus.Varible.State.Bits.OTA=1;
  //RunStatus.Varible.State.Bits.FDD=1;
  //RunStatus.Varible.DR=5; //300bps
  //RunStatus.Varible.BattLevel=255;//continus power supply  
}
/*******************Event of LoRaWAN for users****************************************************/
void MT_HookUserEvent( mt_ev_t ev ,u1_t port,u1_t * Buffer, u2_t len)
{
  //u1_t OutBuf[256];
  //u1_t OutLen=0;
  switch( ev ) 
  {
  case MT_EV_TXDONE: 	   // while the rf data transmitting done
        if(mt_dtu_resetAfterLWT) mpos_driver.mcureset();
        break;
  case MT_EV_JOINED:	   // when the module joined the network successfully
        break; 
  case MT_EV_JOIN_FAILED:  // the join failed
	break;   
  case MT_EV_REJOIN_FAILED: // rejoin failed 
	break; 
  case MT_EV_TXOVER_NOPORT: // mean the transmmite over and no downlink data   
        MT_AUX_LED_OFF();
  	break; 
  case MT_EV_TXOVER_NACK:   // mean the transmmite data is over which need a ack but failed to get a ack
	break; 
  case MT_EV_TXOVER_DNW1:   // mean that module get a downlink data at the window 1th
  case MT_EV_TXOVER_DNW2:   // mean that module get a downlink data at the window 2th
  	MT_AUX_LED_OFF();
        MT_DN_Process(Buffer,(u1_t)len,port); 
	break;     
  case MT_EV_TXOVER_PING:    break;  // mean that module get a downlink data at a ping slot which is used for class B
  case MT_EV_BEACON_TRACKED: break;  // means that module tracked a beacon
  case MT_EV_BEACON_MISSED:  break;  // means that module lost a beacon
  case MT_EV_LOST_TSYNC:     break;  // means that module lost a time sync
  case MT_EV_LINK_ALIVE:     break;  // means that the connection wiht server is alive
  case MT_EV_LINK_DEAD:      break;  //means that the link of module to server is dead
  case MT_EV_MICWRONG:	     break;  // means that module get a data but the mic is erro
  case MT_EV_NTRX:           break;
  case MT_EV_SWRXDONE:       break;
  default:	             break;
  } 
}