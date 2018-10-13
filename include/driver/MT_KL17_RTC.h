#ifndef __MT_KL17_RTC__H
#define __MT_KL17_RTC__H
#include "MKL17Z644.h"
#include "MP_OS_type.h"
extern void RTC_Init(void);
extern void RTC_ConvertSecondsToDatetime(uint32_t seconds, T_RTC_DATETIME *datetime);
extern uint32_t RTC_ConvertDatetimeToSeconds(T_RTC_DATETIME *datetime);
extern void RTC_SetDatetime(T_RTC_DATETIME *datetime);
extern void RTC_GetDatetime(T_RTC_DATETIME *datetime);
extern uint32_t RTC_GetSencond(void);
extern void RTC_SetSencond(uint32_t second);
extern void RTC_SetAlarm(uint32_t interval);
#endif