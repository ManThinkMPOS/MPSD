/*****************************************************************************
 * (c) Copyright 2011, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flash_kinetis.h
 * @author    R20253
 * @version   1.0.8.0
 * @date      Dec-13-2012
 * @brief     Flash programming driver header file
 * @par       
 * @include   
 * @par       
 * @include         
 ******************************************************************************/
#ifndef _MT_KL17_FLASH_H
#define _MT_KL17_FLASH_H

#include "stdio.h"
#include "MKL17Z644.h"

/* For KL Series Flash Program */
#define FLASH_BASE_PTR                FTFA_BASE_PTR
#define FLASH_FSTAT                   FTFA_FSTAT                                  
#define FLASH_FSTAT_CCIF_MASK         FTFA_FSTAT_CCIF_MASK
#define FLASH_FSTAT_ACCERR_MASK       FTFA_FSTAT_ACCERR_MASK
#define FLASH_FSTAT_FPVIOL_MASK       FTFA_FSTAT_FPVIOL_MASK
#define FLASH_FSTAT_RDCOLERR_MASK     FTFA_FSTAT_RDCOLERR_MASK
#define FLASH_FSTAT_MGSTAT0_MASK      FTFA_FSTAT_MGSTAT0_MASK                            
#define FLASH_PROGRAM                 FLASH_ProgramSectionByLongs

//  Flash hardware algorithm operation commands 
#define FLASH_PROGRAM_LONGWORD    0x06
#define FLASH_PROGRAM_PHRASE      0x07
#define FLASH_ERASE_SECTOR        0x09
#define FLASH_READ_Once           0x41
#define FLASH_PROGRAM_Once        0x43

#define FCCOB_REGS  12
#define FLASH_OK     0
#define FLASH_FAIL   1

#define FLASH_BURST_RAM_ADDR (uint32_t*)0x14000000
#define FLASH_BURST_RAM_SIZE	64


#define ERASE_BLOCK_INDEX       4
#define PROGRAM_LONGWORD_INDEX  8
#define PROGRAM_PHRASE_INDEX    12

//  FCOOB register structure
typedef union 
{
  uint8_t all[FCCOB_REGS];
  struct
  {
    uint8_t fccob3;
    uint8_t fccob2;
    uint8_t fccob1;
    uint8_t fccob0;
    uint8_t fccob7;
    uint8_t fccob6;
    uint8_t fccob5;
    uint8_t fccob4;
    uint8_t fccobB;
    uint8_t fccobA;
    uint8_t fccob9;
    uint8_t fccob8;
  }regs;
  
  struct
  {
    uint32_t fccob3210;
    uint32_t fccob7654;
    uint32_t fccobBA98;
  }regsLong;
}FCC0B_STR;

#endif




