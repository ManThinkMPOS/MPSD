/*
 * File:		smc.h
 * Purpose:     Provides low power mode entry routines
 *
 * Notes:
 */

#ifndef __SMC_H__
#define __SMC_H__

#include "stdio.h"
#include "MKL17Z644.h"

/********************************************************************/

// function prototypes
void sleep(void);
void deepsleep(void);
int enter_vlpr(void);
void exit_vlpr(void);
void enter_vlps(void);
void enter_lls(void);
void enter_vlls3(void);
void enter_vlls2(void);
void enter_vlls1(void);
void enter_vlls0(unsigned char PORPO_value);
void enter_vlls0_nopor(void);

/********************************************************************/
#endif /* __SMC_H__ */
