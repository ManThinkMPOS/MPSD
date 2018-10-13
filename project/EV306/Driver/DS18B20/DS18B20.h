#ifndef __DS18B20__H
#define __DS18B20__H
#include "MKL17Z644.h"
/*********************************************************************************************************
** define
*********************************************************************************************************/
#define W_DS_OUT()        do {GPIO_Config(PORTD, 7, GPIO_Mode_OPP);}while(0)
#define W_DS_IN()         do {GPIO_Config(PORTD, 7, GPIO_Mode_IFT);}while(0)
#define W_DS_H()          do {GPIO_PinSet(GPIOD, 7, SET);}while(0)
#define W_DS_L()          do {GPIO_PinSet(GPIOD, 7, RESET);}while(0)

/*********************************************************************************************************
** function
*********************************************************************************************************/
extern uint8_t R_DS_IN(void);
extern bool DS18B20_Iint(void);
extern void DS_WriteByte(uint8_t dat);
extern uint8_t DS_ReadByte(void);
extern bool DS18B20_ReadTemp(int8_t *temp);
#endif
























