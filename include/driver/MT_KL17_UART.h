#ifndef _MT_KL17_UART_H
#define _MT_KL17_UART_H

#include "MKL17Z644.h"

extern void UART1_Init(uint32_t baudrate);
extern unsigned char USART1_SendByte(unsigned char data);
extern unsigned char UART1_SendBuffer(unsigned char* data,unsigned short len); //长数据包发送，需要加踢狗
extern void UART1_SendString(unsigned char * sendData);
extern void UART1_Sendhex(unsigned char* data,unsigned short len);
extern void UART1_SendDec(signed long long data);
#endif
