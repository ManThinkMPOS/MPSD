#ifndef _MY_TYPE_H
#define _MY_TYPE_H
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
#include "string.h"

typedef union {
  uint16_t u16;               // element specifier for accessing whole u16
  int16_t i16;                // element specifier for accessing whole i16
  struct {
    uint8_t u8L;              // element specifier for accessing low u8
    uint8_t u8H;              // element specifier for accessing high u8
  }PACKED s16;                // element spec. for acc. struct with low or high u8
}PACKED nt16;

typedef struct t_MT_Sensor_para
    {
        u1_t    Command;		      
        u1_t    InforFormat; 
        u1_t    MType;
        u1_t    HwVersion;
        u1_t    FmVersion;
	union {
	u1_t   AlarmState;				
	struct {	
                       u1_t        Sht20Status:1;	//0:normal  1:abnormal
                       u1_t        Ds18b20Status :1;
                       u1_t        AccStatus:1;
                       u1_t        RFU1 :1;
                       u1_t        RFU2 :2;
                       u1_t        RFU3 :2;
                }Bits;
         }AlarmStatus;   
         u1_t   Sht20Temp[2];     
         u1_t   Sht20Hum[2];
         s1_t   Ds18b20Temp; 
         u1_t   ACC_X[2];
         u1_t   ACC_Y[2];
         u1_t   ACC_Z[2];
         u1_t   Vol; 
         u1_t   RSSI;
         u1_t   SNR;
    }PACKED T_MT_Sensor_PARA; 

typedef union U_MT_Sensor_PARA
{
  T_MT_Sensor_PARA MPRegister;
  unsigned char Bytes[20];
} PACKED U_MT_SensorPARA;

typedef struct u_senspropertypara
{
        u1_t MType;
	u1_t Hwversion;
	u1_t Fmversion; 
        u1_t UpInterval[2];
	u1_t Resv[6];
}PACKED MT_Sensor_InfoPara;

#endif