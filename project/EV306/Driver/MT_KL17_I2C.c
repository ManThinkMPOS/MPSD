#include "MT_KL17_I2C.h"
#include "MKL17Z644.h"
#include "include.h"

/********************************************************
* Function for SDA_IN 
* input£º none
* output: none
*
********************************************************/
uint8_t SDA_IN(void)
{
    return GPIO_PinGet(GPIOC, 2);
}
/********************************************************
* Function for SDA_IN 
* input£º none
* output: none
*
********************************************************/
uint8_t SCL_IN(void)
{
    return GPIO_PinGet(GPIOC, 1);
}
/********************************************************
* Function for I2C1 Initial 
* input£º none
* output: none
*
********************************************************/
void I2C_Init(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    GPIO_Config(PORTC, 2, GPIO_Mode_OPP);//PTC2->I2C_SDA
    GPIO_PinSet(GPIOC, 2, SET);
    GPIO_Config(PORTC, 1, GPIO_Mode_OPP);//PTC1->I2C_SCL
    GPIO_PinSet(GPIOC, 1, SET);
}
/********************************************************
* Function for I2C_Start 
* input£º none
* output: none
*
********************************************************/
bool I2C_Start(void)
{
    SDA_H();
    SCL_H();
    I2C_DELAY();
    SDA_L();
    I2C_DELAY();
    SCL_L();
    return true;
}
/********************************************************
* Function for I2C_Stop 
* input£º none
* output: none
*
********************************************************/
void I2C_Stop(void)
{
    SCL_L();
    SDA_L();
    I2C_DELAY();
    SCL_H();
    SDA_H();
    I2C_DELAY();
}
/********************************************************
* Function for I2C_Ack 
* input£º none
* output: none
*
********************************************************/
void I2C_Ack(void)
{
    SCL_L();
    I2C_DELAY();
    SDA_L();
    I2C_DELAY();
    SCL_H();
    I2C_DELAY();
    SCL_L();
    I2C_DELAY();
}
/********************************************************
* Function for I2C_NAck 
* input£º none
* output: none
*
********************************************************/
void I2C_NAck(void)
{
    SCL_L();
    I2C_DELAY();
    SDA_H();
    I2C_DELAY();
    SCL_H();
    I2C_DELAY();
    SCL_L();
    I2C_DELAY();
}
/********************************************************
* Function for I2C_WaitAck 
* input£º none
* output: none
*
********************************************************/
bool I2C_WaitAck(void)
{
    uint8_t err_time=0;
    SDA_DDR_IN();
    SDA_H();
    I2C_DELAY();
    SCL_H();
    I2C_DELAY();
    while(SDA_IN())
    {
        err_time++;
        if(err_time>200)
        {
            I2C_Stop();
            return true;
        }
    }
    SCL_L();
    SDA_DDR_OUT();
    return false;
}
/********************************************************
* Function for I2C_SendByte 
* input£º none
* output: none
*
********************************************************/
void I2C_SendByte(uint8_t data)
{
    volatile uint8_t i;
    
    i = 8;
    while(i--)
    {
        if(data & 0x80) SDA_H();
        else SDA_L();
        data <<= 1;
        I2C_DELAY();
        SCL_H();
        I2C_DELAY();
        SCL_L();
        I2C_DELAY();
    }

}
/********************************************************
* Function for I2C_GetByte 
* input£º none
* output: none
*
********************************************************/
uint8_t I2C_GetByte(void)
{
    uint8_t i,byte;
    
    i = 8;
    byte = 0;

    SDA_DDR_IN();
    I2C_DELAY();
    while(i--)
    {
        SCL_L();
        I2C_DELAY();
        SCL_H();
        I2C_DELAY();
        byte = (byte<<1)|(SDA_IN() & 1);
    }
    SCL_L();
    SDA_DDR_OUT();
    I2C_DELAY();
    return byte;
}
/********************************************************
* Function for I2C_GetByte 
* input£º none
* output: none
*
********************************************************/
int I2C_WriteBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len)
{
    uint8_t err;

    err = 0;
    //chipAddr <<= 1;
    
    I2C_Start();
    I2C_SendByte(chipAddr);
    err += I2C_WaitAck();

    I2C_SendByte(addr);
    err += I2C_WaitAck();

    while(len--)
    {
        I2C_SendByte(*buf++);
        err += I2C_WaitAck();  
    }

    I2C_Stop();
    return err;
}
/********************************************************
* Function for I2C_WriteSingleRegister 
* input£º none
* output: none
*
********************************************************/
int I2C_WriteSingleRegister(uint8_t chipAddr, uint8_t addr, uint8_t data)
{
    return I2C_WriteBuffer(chipAddr, addr, &data, 1);
}

/********************************************************
* Function for I2C_ReadBuffer 
* input£º none
* output: none
*
********************************************************/
int I2C_ReadBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len)
{

    uint8_t err;
 
    err = 0;
    
    I2C_Start();
    I2C_SendByte(chipAddr);
    err += I2C_WaitAck();
    
    if(len>1) addr|=0x80;
    I2C_SendByte(addr);
    err += I2C_WaitAck();

    
    I2C_Start();
    I2C_SendByte(chipAddr+1);
    err += I2C_WaitAck();
    
    while(len--)
    {
        *buf++ = I2C_GetByte();
        if(len)
        {
            I2C_Ack();
        }
    }
    
    I2C_NAck();
    I2C_Stop();
    
    return err;
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/ 








