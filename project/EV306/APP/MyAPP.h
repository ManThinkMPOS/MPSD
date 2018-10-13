#ifndef __MyAPP__H
#define __MyAPP__H
#include "MKL17Z644.h"
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
#include "string.h"

extern void MT_MyHookInit();
extern void MT_MyParaInit();
extern void MT_SetupSensorTxTask();
extern void MT_SetupOnceEventTask();
extern void MT_app_HookAPPParaChanged(u1_t * paras);

#endif