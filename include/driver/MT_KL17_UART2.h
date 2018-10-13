#ifndef _MT_KL17_UART2_H
#define _MT_KL17_UART2_H

#include "MKL17Z644.h"

extern void UART2_Init(uint32_t baudrate);
extern unsigned char USART2_SendByte(unsigned char data);
extern unsigned char UART2_SendBuffer(unsigned char* data,unsigned short len); //长数据包发送，需要加踢狗
extern void UART2_SendString(unsigned char * sendData);
extern void UART2_Sendhex(unsigned char* data,unsigned short len);
extern void UART2_SendDec(signed long long data);
#endif
