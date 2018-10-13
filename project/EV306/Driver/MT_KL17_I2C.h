#ifndef __MT_KL17_I2C__H
#define __MT_KL17_I2C__H
#include "MKL17Z644.h"
/*********************************************************************************************************
** global
*********************************************************************************************************/
#define SDA_DDR_OUT()       do {GPIO_Config(PORTC, 2, GPIO_Mode_OPP);}while(0)
#define SDA_DDR_IN()        do {GPIO_Config(PORTC, 2, GPIO_Mode_IFT);}while(0)
#define SCL_DDR_OUT()       do {GPIO_Config(PORTC, 1, GPIO_Mode_OPP);}while(0)
#define SCL_DDR_IN()        do {GPIO_Config(PORTC, 1, GPIO_Mode_IFT);}while(0)
#define SDA_H()             do {GPIO_PinSet(GPIOC, 2, SET);}while(0)
#define SDA_L()             do {GPIO_PinSet(GPIOC, 2, RESET);}while(0)
#define SCL_H()             do {GPIO_PinSet(GPIOC, 1, SET);}while(0)
#define SCL_L()             do {GPIO_PinSet(GPIOC, 1, RESET);}while(0)
#define I2C_DELAY()         mpos_osfun.DelayUs(6);
/*********************************************************************************************************
 define
*********************************************************************************************************/
#define MKL_I2C0            0
#define MKL_I2C1            1
    
#define I2C_MASTER          0
#define I2C_SLAVER          1
  
#define I2C_ADDRESS_SHORT   0                                               /* 7位从地址模式          */
#define I2C_ADDRESS_LONG    1                                               /* 10位从地址模式         */
    
#define NONE_SUBA           0                                               /* 无子地址模式           */
#define ONE_BYTE_SUBA       1                                               /* 单字节子地址模式       */
#define TWO_BYTE_SUBA       2                                               /* 双字节子地址模式       */
  
#define I2C1_MODE                   0 

#define I2C1_SLAVER_ADDRESS_MODE    0

#define I2C1_BAUD_RATE              100000

#define I2C1_SLAVER_ADR             0xA0  
#define I2C1_RANGE_SLAVER_ADR       0xAB
#define I2C1_SLAVER_ADR_MATCH       0x0  

/* 计算波特率公式 BT = BusCLK/(1 << MUL)/SCL_DIVIDE */  
#define I2C1_MUL             1             /* 分频设置           */
#define I2C1_BT_ERROR        50            /* I2C波特率最大误差  */  

#define DEFAULT_BUS_CLOCK    24000000u     /* Default bus clock value */  

typedef struct t_i2c_para
    {
        volatile u1_t     sla;              /* I2C器件从地址              */
        volatile u4_t     suba;             /* I2C期间内子地址            */
        volatile u1_t     suba_num;         /* I2C子地址长度              */
        volatile u1_t     *buf;             /* 数据缓冲区指针         */
        volatile u4_t     num;              /* 要读取和写入的数据个数     */
        volatile u1_t     end;              /* I2C总线结束标志            */
        volatile u1_t     restart;          /* I2C总线重复标志            */
        
        volatile u1_t     irq_status;       /* I2C中断读写操作控制        */                                                                      /* 0--写模式                  */
        volatile u1_t     sla_dir;          /* 从机控制 1--读取操作  0--写操作*/
    }PACKED T_I2C_PARA;

extern void I2C_Init(void);
extern bool I2C_Start(void);
extern void I2C_Stop(void);
extern void I2C_SendByte(uint8_t data);
extern uint8_t I2C_GetByte(void);
extern u1_t I2C1_SendByte(u1_t sla, u1_t *dat);
extern int I2C_WriteBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len);
extern int I2C_ReadBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len);
extern void delay_us(uint16_t nCount);
extern uint8_t SCL_IN(void);
extern void I2C_Init(void);
extern void I2C_Ack(void);
extern void I2C_NAck(void);
extern bool I2C_WaitAck(void);
#endif
























