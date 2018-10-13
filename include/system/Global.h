#ifndef __EXGLOBAL__H
#define __EXGLOBAL__H
#include "MP_OS_type.h"
#include "MP_LWS_type.h"
extern u2_t (*Hook_UARTReceive)(u1_t * rxBuffer, u2_t len,u1_t * txBuffer);
extern S_HookEvent Hook_Event;
extern U_CROFW 	FwReg;
extern U_CRORD 	RdReg;
extern U_CROCF  CFReg;
extern U_CRO_APP  appPara;
extern U_RunStatus   	RunStatus;
extern U_SYSSTATUS  	SysStatus;
extern S_LPINFO 	LPInfo;;
extern TLWSFUC StackFunction;
extern T_RTC_DATETIME  SysTime;
extern u2_t globalRand;
extern T_MP_CONTRL_BIT mp_controlbits ;
extern T_MP_FUN_DRIVER mpos_driver;
extern T_MP_FUN_OS     mpos_osfun;
extern T_MP_FUN_LWS    mpos_lws;
#endif
