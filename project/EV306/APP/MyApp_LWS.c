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

#define _OM402O_
//#define _OM802O_

//static U_CROFW paraFwReg;      // parameters of the firmware which defines the parameters of LoRaWAN
//static U_CRORD paraRdReg;      // parameters of radio which include the frequency and the band
//static U_CROCF paraCFReg;      // parameters of Config which include the cofigure parameter 
//static u1_t AppKey[16]={0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C}; // APP key used for LoRaWAN
//static u8_t AppEui;
//static u4_t StartFreq;
//static u4_t Dn2Freq;
//static bool FDDStatus;
/**********************Initialization of LoRaWAN******************************************************************/
void MT_LoRaWANParaInitial()
{
/*
#ifdef _OM402O_
  AppEui= 0x8100000002000001;
  StartFreq=470300000;
  Dn2Freq=505300000;
  FDDStatus=true;
#endif
#ifdef _OM802O_
  AppEui= 0x8100000005000001;
  StartFreq=868100000;
  Dn2Freq=869525000;
  FDDStatus=false;
#endif
  RunStatus.Varible.State.Bits.JoinStatus=0;
  RunStatus.Varible.State.Bits.Mode=1;// classA
  RunStatus.Varible.State.Bits.ADR=1;
  RunStatus.Varible.State.Bits.ServerADR=0;
  RunStatus.Varible.State.Bits.OTA=0;
  RunStatus.Varible.State.Bits.FDD=FDDStatus;
  RunStatus.Varible.State.Bits.LinkCheck=0;
  RunStatus.Varible.DR=0; //300bps
  RunStatus.Varible.BattLevel=255;//continus power supply
*/  
  /* Configue the FW parameter*/
/*  mpos_lws.paraFWGet(&paraFwReg);
  paraFwReg.SFwRegister.RxWinDelay1=1;
  paraFwReg.SFwRegister.RxWinDelay2=2;
  paraFwReg.SFwRegister.JoinDelay1=5;
  paraFwReg.SFwRegister.JoinDelay2=6;
  paraFwReg.SFwRegister.ReTx=5;
  paraFwReg.SFwRegister.globalDutyRate=0;
  paraFwReg.SFwRegister.DevTimeReqDuty=0;
  for(int i=0;i<4;i++)
  {
  	paraFwReg.SFwRegister.DutyBand[i][0]=0;
	paraFwReg.SFwRegister.DutyBand[i][1]=0;
  }
  mpos_osfun.os_wlsbf8(paraFwReg.SFwRegister.AppEui,AppEui);
  mpos_osfun.memcpy1(paraFwReg.SFwRegister.DevKey,AppKey,16);
  mpos_lws.paraFWSave(&paraFwReg);
*/  
  /* Configue the RD parameter*/
/*mpos_lws.paraRDGet(&paraRdReg);
  paraRdReg.SRdRegister.dn2Dr=0; paraRdReg.SRdRegister.Power=22; 
  mpos_osfun.os_wlsbf4(paraRdReg.SRdRegister.dn2Freq,Dn2Freq);
  mpos_osfun.os_wlsbf2(paraRdReg.SRdRegister.channelMap,0x00FF);
  for(int i=0;i<16;i++) 
  {
    mpos_osfun.os_wlsbf4(paraRdReg.SRdRegister.Freq[i].SFreq,(StartFreq+200000*i)|(i/2));
    paraRdReg.SRdRegister.Freq[i].DRRange.Bits.HiDr=5;
    paraRdReg.SRdRegister.Freq[i].DRRange.Bits.LoDr=0;
  }
  paraRdReg.SRdRegister.aliCHcntl=0x02;  
  mpos_lws.paraRDSave(&paraRdReg);
*/  
  /* Configue the CF parameter*/  
/*mpos_lws.paraCFGet(&paraCFReg);
  paraCFReg.CFRegister.exStackFunction.ByteS = 0x03;
  paraCFReg.CFRegister.JoinCHMap[0] = 0x02;
  paraCFReg.CFRegister.JoinCHMap[1] = 0x0;
  mpos_osfun.os_wlsbf4(paraCFReg.CFRegister.SWFreq,494000000);
  paraCFReg.CFRegister.SWSF=10;paraCFReg.CFRegister.SWBW=7;
  paraCFReg.CFRegister.SWPeriod=80;
  mpos_lws.paraCFSave(&paraCFReg);
*/
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
        MT_AUX_LED_OFF();
        break; 
  case MT_EV_JOIN_FAILED:  // the join failed
        MT_AUX_LED_OFF();
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