#ifndef __INCLUDE__H__
#define __INCLUDE__H__
#include "stdio.h"
#include "MKL17Z644.h"
#include "MT_KL17_GPIO.h"
#include "MT_KL17_Flash.h"
#include "MP_OS_type.h"
#include "MP_LWS_type.h"
#include "MP_LWS.h"
#include "Global.h"
#include "MP_OS.h"
#define LW_BUSY         1
#define LW_IDLE         0

#define STATUS_IDLE 	0x00
#define STATUS_TODEAL 	0x01
#define STATUS_TXING 	0x02
#define STATUS_TXDONE 	0x03
#define STATUS_RXOPEN1 	0x04
#define STATUS_RXDONE1  0x05
#define STATUS_RXOPEN2  0x06
#define STATUS_RXDONE2  0x07

#define STATUS_RXSCAN  	    0x01
#define STATUS_RXOPENBcn    0x02
#define STATUS_RXDONEBcn    0x03
#define STATUS_RXOPENPing   0x04
#define STATUS_RXDONEPing   0x05
#define STATUS_RXOPENMULTI  0x06
#define STATUS_RXDONEMULTI  0x07

#define STATUS_RXOPENClassC 0x06
#define STATUS_RXDONEClassC 0x07

#define STATUS_RXOPENCA     0x03
#define STATUS_RXOPENClassD 0x04
#define STATUS_RXDONEClassD 0x05

#define WKMOD_NO	0x00
#define WKMOD_RTC	0x01
#define WKMOD_UART      0x02
#define WKMOD_ARRM      0x04
#define WKMOD_INT       0x03

#define SLPMOD_NO	0x00
#define SLPMOD_TODEAL   0x01
#define SLPMOD_WDOG	0x02
#endif