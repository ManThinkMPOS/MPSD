#include "SHT20.h"
#include "MKL17Z644.h"
#include "Global.h"
#include "include.h"
#include "MyGlobal.h"
#include "MT_KL17_I2C.h"
const uint16_t POLYNOMIAL_SHT20 = 0x131;  //P(x)=x^8+x^5+x^4+1 = 100110001
//==============================================================================
uint8_t SHT2x_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum)
//==============================================================================
{
  uint8_t crc = 0;	
  uint8_t byteCtr;
  //calculates 8-Bit checksum with given polynomial
  for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
  { crc ^= (data[byteCtr]);
    for (uint8_t bit = 8; bit > 0; --bit)
    { if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL_SHT20;
      else crc = (crc << 1);
    }
  }
  if (crc != checksum) return CHECKSUM_ERROR;
  else return 0;
}

//===========================================================================
uint8_t SHT2x_ReadUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
  uint8_t checksum;   //variable for checksum byte
  uint8_t error=0;    //variable for error code

  I2C_Start();
  I2C_SendByte (I2C_ADR_W);
  error += I2C_WaitAck();
  I2C_SendByte (USER_REG_R);
  error += I2C_WaitAck();
  
  I2C_Start();
  I2C_SendByte (I2C_ADR_R);
  error += I2C_WaitAck();
  *pRegisterValue = I2C_GetByte();I2C_Ack();
  
  checksum=I2C_GetByte();I2C_NAck();
  error |= SHT2x_CheckCrc (pRegisterValue,1,checksum);
  I2C_Stop();
  return error;
}

//===========================================================================
uint8_t SHT2x_WriteUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
  uint8_t error=0;   //variable for error code
  
  I2C_Start();
  I2C_SendByte (I2C_ADR_W);
  error += I2C_WaitAck();
  I2C_SendByte (USER_REG_W);
  error += I2C_WaitAck();
  I2C_SendByte (*pRegisterValue);
  error += I2C_WaitAck();
  I2C_Stop();
  return error;
}

//===========================================================================
uint8_t SHT2x_MeasureHM(etSHT2xMeasureType eSHT2xMeasureType, nt16 *pMeasurand)
//===========================================================================
{
  uint8_t  checksum;   //checksum
  uint8_t  data[2];    //data array for checksum verification
  uint8_t  error=0;    //error variable


  //-- write I2C Sensor address and command --
  I2C_Start();
  I2C_SendByte (I2C_ADR_W); // I2C Adr
  error += I2C_WaitAck();
  switch(eSHT2xMeasureType)
  { case HUMIDITY: I2C_SendByte (TRIG_RH_MEASUREMENT_HM);error += I2C_WaitAck(); break;
    case TEMP    : I2C_SendByte (TRIG_T_MEASUREMENT_HM); error += I2C_WaitAck(); break;
    default: ;//assert(0);
  }
  //-- wait until hold master is released --
  I2C_Start();
  I2C_SendByte (I2C_ADR_R);
  error += I2C_WaitAck();
  //SCL_DDR_IN();
  mpos_osfun.DelayUs(150000);
  //SCL_DDR_OUT();
  pMeasurand->s16.u8H = data[0] = I2C_GetByte();I2C_Ack();
  pMeasurand->s16.u8L = data[1] = I2C_GetByte();I2C_Ack();
  checksum=I2C_GetByte();I2C_NAck();
  //-- verify checksum --
  error |= SHT2x_CheckCrc (data,2,checksum);
  I2C_Stop();
  return error;
}
//===========================================================================
uint8_t SHT2x_MeasurePoll(etSHT2xMeasureType eSHT2xMeasureType, nt16 *pMeasurand)
//===========================================================================
{
  uint8_t  checksum;   //checksum
  uint8_t  data[2];    //data array for checksum verification
  uint8_t  error=0;    //error variable

  //-- write I2C Sensor address and command --
  I2C_Start();
  I2C_SendByte (I2C_ADR_W); // I2C Adr
  error += I2C_WaitAck();
  switch(eSHT2xMeasureType)
  { case HUMIDITY: I2C_SendByte (TRIG_RH_MEASUREMENT_POLL);error += I2C_WaitAck(); break;
    case TEMP    : I2C_SendByte (TRIG_T_MEASUREMENT_POLL); error += I2C_WaitAck(); break;
    default: ;//assert(0);
  }
  mpos_osfun.DelayUs(30);
  I2C_Stop();
  mpos_osfun.DelayUs(150000);
  //-- poll every 10ms for measurement ready. Timeout after 20 retries (200ms)--
  I2C_Start();
  I2C_SendByte(I2C_ADR_R);
  error = I2C_WaitAck();
  //-- read two data bytes and one checksum byte --
  pMeasurand->s16.u8H = data[0] = I2C_GetByte();I2C_Ack();
  pMeasurand->s16.u8L = data[1] = I2C_GetByte();I2C_Ack();
  checksum=I2C_GetByte();I2C_NAck();

  //-- verify checksum --
  error |= SHT2x_CheckCrc (data,2,checksum);
  I2C_Stop();
  return error;
}

//===========================================================================
uint8_t SHT2x_SoftReset()
//===========================================================================
{
  uint8_t  error=0;           //error variable

  I2C_Start();
  I2C_SendByte (I2C_ADR_W); // I2C Adr
  error += I2C_WaitAck();
  I2C_SendByte (SOFT_RESET);          
  error += I2C_WaitAck();// Command
  I2C_Stop();

  mpos_driver.kickdog();   mpos_osfun.DelayUs(300000);  // wait till Sensor has restarted
  return error;
}

//==============================================================================
float SHT2x_CalcRH(uint16_t u16sRH)
//==============================================================================
{
  float humidityRH;              // variable for result

  u16sRH &= ~0x0003;          // clear bits [1..0] (status bits)
  //-- calculate relative humidity [%RH] --

  humidityRH = -6.0 + 125.0/65536 * (float)u16sRH; // RH= -6 + 125 * SRH/2^16
  return humidityRH;
}

//==============================================================================
float SHT2x_CalcTemperatureC(uint16_t u16sT)
//==============================================================================
{
  float temperatureC;            // variable for result

  u16sT &= ~0x0003;           // clear bits [1..0] (status bits)
  //u16sT = (u16sT>>2);
  //-- calculate temperature [?C] --
  temperatureC= -46.85 + 175.72/65536 *(float)u16sT; //T= -46.85 + 175.72 * ST/2^16
  return temperatureC;
}

//==============================================================================
uint8_t SHT2x_GetSerialNumber(uint8_t u8SerialNumber[])
//==============================================================================
{
  uint8_t  error=0;                          //error variable

  //Read from memory location 1
  I2C_Start();
  I2C_SendByte (I2C_ADR_W);    //I2C address
  error += I2C_WaitAck();
  I2C_SendByte (0xFA);         //Command for readout on-chip memory
  error += I2C_WaitAck();
  I2C_SendByte (0x0F);         //on-chip memory address
  error += I2C_WaitAck();

  I2C_Start();
  I2C_SendByte (I2C_ADR_R);    //I2C address
  error += I2C_WaitAck();

  u8SerialNumber[5] = I2C_GetByte();  I2C_Ack(); //Read SNB_3
  I2C_GetByte();  I2C_Ack();        //Read CRC SNB_3 (CRC is not analyzed)
  u8SerialNumber[4] = I2C_GetByte(); I2C_Ack(); //Read SNB_2  
  I2C_GetByte();  I2C_Ack();                    //Read CRC SNB_2 (CRC is not analyzed)  
  u8SerialNumber[3] = I2C_GetByte();I2C_Ack();  //Read SNB_1
  I2C_GetByte();   I2C_Ack();                      //Read CRC SNB_1 (CRC is not analyzed)
  u8SerialNumber[2] = I2C_GetByte(); I2C_Ack(); //Read SNB_0
  I2C_GetByte();  I2C_NAck();                //Read CRC SNB_0 (CRC is not analyzed)
  I2C_Stop();

  //Read from memory location 2
  I2C_Start();
  I2C_SendByte (I2C_ADR_W);    //I2C address
  error += I2C_WaitAck();
  I2C_SendByte (0xFC);         //Command for readout on-chip memory
  error += I2C_WaitAck();
  I2C_SendByte (0xC9);         //on-chip memory address
  error += I2C_WaitAck();
  
  I2C_Start();
  I2C_SendByte (I2C_ADR_R);    //I2C address
  error += I2C_WaitAck();
  u8SerialNumber[1] = I2C_GetByte(); I2C_Ack();//Read SNC_1
  u8SerialNumber[0] = I2C_GetByte(); I2C_Ack();//Read SNC_0
  I2C_GetByte();  I2C_Ack();                   //Read CRC SNC0/1 (CRC is not analyzed)
  u8SerialNumber[7] = I2C_GetByte();I2C_Ack(); //Read SNA_1
  u8SerialNumber[6] = I2C_GetByte();I2C_Ack(); //Read SNA_0
  I2C_GetByte();  I2C_NAck();               //Read CRC SNA0/1 (CRC is not analyzed)
  I2C_Stop();
  return error;
}
//==============================================================================
bool SHT2x_MeasureTH(u1_t buff[])
//==============================================================================
{
    nt16 sRH;
    nt16 sT; 
    uint8_t error=0;
    uint16_t temperatureC;
    uint16_t humidityRH;
    error += SHT2x_MeasurePoll(TEMP, &sT);
    error += SHT2x_MeasurePoll(HUMIDITY, &sRH);
    if(error!=0) 
    {
      SHT2x_SoftReset();
      error += SHT2x_MeasurePoll(TEMP, &sT);
      error += SHT2x_MeasurePoll(HUMIDITY, &sRH);
      if(error!=0) return false;
    }
    temperatureC = (uint16_t)(SHT2x_CalcTemperatureC(sT.u16)*10)+1000;  //temperature = test*10+1000
    humidityRH = (uint16_t)(SHT2x_CalcRH(sRH.u16)*10);           //humidity = test*10
    buff[0] = temperatureC;
    buff[1] = (temperatureC>>8);
    buff[2] = humidityRH;
    buff[3] = (humidityRH>>8);    
    return true;
}
