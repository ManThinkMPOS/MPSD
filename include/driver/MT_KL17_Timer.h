#ifndef _MT_KL17_Timer_H
#define _MT_KL17_Timer_H

#include "MKL17Z644.h"
void PIT_Config(void);
void LPTIM_Config(void);
void PIT_Cmd(uint8_t state);
void LPTIM_Cmd(uint8_t state);
void LPTIM_SetWakeUpCounter(uint16_t count);
#endif