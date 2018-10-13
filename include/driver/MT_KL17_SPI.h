#ifndef __MT_KL17_SPI__H
#define __MT_KL17_SPI__H
#include "MKL17Z644.h"
extern void Spi_Init(SPI_Type* SPIx);
extern unsigned char SpiInOut(SPI_Type* SPIx,unsigned char outData);
extern void SPI_Cmd(SPI_Type* SPIx,FunctionalState NewState);

#endif
