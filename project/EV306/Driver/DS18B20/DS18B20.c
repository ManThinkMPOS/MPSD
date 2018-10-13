#include "DS18B20.h"
#include "MKL17Z644.h"
#include "include.h"
#include "MyGlobal.h"

/********************************************************
* Function for Read 1-wire data 
* input£º none
* output: none
*
********************************************************/
uint8_t R_DS_IN(void)
{
    return GPIO_PinGet(GPIOD, 7);
}
/********************************************************
* Function for DS18B20_Iint 
* input£º none
* output: none
*
********************************************************/
bool DS18B20_Iint(void)
{
    bool status; 
    W_DS_OUT();
    W_DS_H();
    asm("NOP");
    W_DS_L();
    mpos_osfun.DelayUs(700); //pull down bus, 
    W_DS_IN(); //release bus 
    mpos_osfun.DelayUs(150); //delay time to read
    status = (bool)R_DS_IN(); 
    mpos_osfun.DelayUs(142); //141.95us 
    //DS = 1; 
    asm("NOP");
    return status;
}
/********************************************************
* Function for DS_WriteByte 
* input£º none
* output: none
*
********************************************************/
void DS_WriteByte(uint8_t dat)  
{ 
    uint8_t i; 
    for(i=0;i<8;i++) 
    { 
        W_DS_OUT();
        asm("NOP");
        W_DS_L(); 
        mpos_osfun.DelayUs(1);//generate the write sequence
        if((dat & 0x01)==0x01) W_DS_H();
        else W_DS_L();
        mpos_osfun.DelayUs(77); //76.95us 
        W_DS_IN(); //relase the bus to ready to the next write 
        asm("NOP"); 
        dat >>= 1; 
    } 
}
/********************************************************
* Function for DS_ReadByte 
* input£º none
* output: none
*
********************************************************/
uint8_t DS_ReadByte(void) 
{ 
    uint8_t dat,i,j; 
    for(i=0;i<8;i++) 
    { 
        W_DS_OUT();
        asm("NOP");
        W_DS_L(); 
        asm("NOP"); //generate the write sequence 
        W_DS_IN();
        asm("NOP");//release the bus 
        j = R_DS_IN();
        mpos_osfun.DelayUs(77); //76.95us 
        asm("NOP"); 
        dat = (j<<7)|(dat>>1); //data from lsb to the msb
    } 
    return dat; 
}
/********************************************************
* Function for DS18B20_ReadTemp 
* input£º none
* output: none
*
********************************************************/
bool DS18B20_ReadTemp(int8_t *temp)
{
    uint8_t lsb,msb;
    if(DS18B20_Iint())return false; //initial the DS18B20 
    DS_WriteByte(0xcc); //ignore the ROM instruction
    DS_WriteByte(0x44); //the temp convert instruction 
    mpos_driver.kickdog(); 
    mpos_osfun.DelayUs(1000000);
    mpos_driver.kickdog();
    if(DS18B20_Iint())return false; //initial the DS18B20  
    DS_WriteByte(0xcc); //ignore the ROM instruction 
    DS_WriteByte(0xbe); //read the temp register£» 
    lsb  = DS_ReadByte(); //the low 8 bit 
    msb  = DS_ReadByte(); //the higy 8 bit 
    *temp = (int8_t)((((int16_t)msb << 8) + lsb)*0.0625); 
    return true;
}

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/ 








