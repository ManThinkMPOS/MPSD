#include "LIS2DH12.h"
#include "MKL17Z644.h"
#include "Global.h"
#include "include.h"
#include "lis2dh12_reg.h"
#include "MT_KL17_I2C.h"
#include "math.h"

/* Private variables ---------------------------------------------------------*/
static axis3bit16_t data_raw_acceleration;
static axis1bit16_t data_raw_temperature;
static uint8_t whoamI;
/********************************************************
* Function for platform_write 
*
********************************************************/
int32_t platform_write(void *handle, uint8_t Reg, uint8_t *Bufp,uint16_t len)
{
    /* enable auto incremented in multiple read/write commands */
    //Reg |= 0x80; 
    return I2C_WriteBuffer(LIS2DH12_I2C_ADD_L, Reg, Bufp, len);
}
/********************************************************
* Function for platform_read 
*
********************************************************/
int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,uint16_t len)
{
    /* enable auto incremented in multiple read/write commands */
    //Reg |= 0x80;
    return I2C_ReadBuffer(LIS2DH12_I2C_ADD_L,Reg,Bufp,len);
}
/********************************************************
* Function for Meter_InitIo 
*
********************************************************/
u1_t LIS2DH12_Init(void)
{
  uint8_t i;
  //float acceleration_mg[3];
  //float temperature_degC;
  lis2dh12_reg_t reg;//Read output only if new value is available
  lis2dh12_ctx_t dev_ctx;             // Initialize mems driver interface
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  whoamI = 0;                         //Check device ID
  for(i=0;i<5;i++)
  {
    lis2dh12_device_id_get(&dev_ctx, &whoamI);
    if (whoamI == LIS2DH12_ID) break;
    mpos_osfun.DelayUs(50000);
  }
  if(i>=5) return false;
  lis2dh12_pin_sdo_sa0_mode_set(&dev_ctx,LIS2DH12_PULL_UP_DISCONNECT);//disable the pullup 
  //lis2dh12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);  //Enable Block Data Update
  lis2dh12_filter_reference_get(&dev_ctx, &whoamI);
  lis2dh12_data_rate_set(&dev_ctx, LIS2DH12_ODR_10Hz);//output data to 10 Hz
  lis2dh12_operating_mode_set(&dev_ctx,LIS2DH12_LP_8bit); // set lp==1;
  lis2dh12_full_scale_set(&dev_ctx, LIS2DH12_2g);//Set full scale
  lis2dh12_temperature_meas_set(&dev_ctx, LIS2DH12_TEMP_ENABLE);//Enable temperature Sensor 
  //lis2dh12_int1_gen_threshold_set(&dev_ctx,54);  //886mg/16 =54
  //lis2dh12_int1_gen_duration_set(&dev_ctx,10);// time= 1*ODR
  //lis2dh12_pin_int1_config_set(&dev_ctx,I1_IA1_ENABLE);
  //lis2dh12_int1_gen_conf_set(&dev_ctx,ZLIE_ENABLE); //Enable Y(H) interrupt
  mpos_driver.kickdog();
  mpos_osfun.DelayUs(1000000);
  lis2dh12_status_get(&dev_ctx, &reg.status_reg);
  if (reg.status_reg.zyxda)
  {
    /* Read magnetic field data */
    lis2dh12_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
    //acceleration_mg[0] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[0] );
    //acceleration_mg[1] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[1] );
    //acceleration_mg[2] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[2] ); 
  }
  lis2dh12_temp_data_ready_get(&dev_ctx, &reg.byte);      
  if (reg.byte)      
  {
    /* Read temperature data */
    lis2dh12_temperature_raw_get(&dev_ctx, data_raw_temperature.u8bit);
    //temperature_degC = LIS2DH12_FROM_LSB_TO_degC_LP( data_raw_temperature.i16bit );
  }
  return true;
}

/********************************************************
* Function for LIS2DH12_AngleCheck
*
********************************************************/
void LIS2DH12_LowPower(void)
{
  uint8_t temp;
  lis2dh12_ctx_t dev_ctx;             // Initialize mems driver interface
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  lis2dh12_pin_sdo_sa0_mode_set(&dev_ctx,LIS2DH12_PULL_UP_DISCONNECT);//disable the pullup 
  //lis2dh12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);  //Enable Block Data Update
  lis2dh12_filter_reference_get(&dev_ctx, &temp);
  lis2dh12_data_rate_set(&dev_ctx, LIS2DH12_POWER_DOWN);//output data to 10 Hz
  lis2dh12_operating_mode_set(&dev_ctx,LIS2DH12_LP_8bit); // set lp==1;
  lis2dh12_full_scale_set(&dev_ctx, LIS2DH12_2g);//Set full scale
  lis2dh12_temperature_meas_set(&dev_ctx, LIS2DH12_TEMP_DISABLE);//Enable temperature Sensor
}
/********************************************************
* Function for LIS2DH12_Read
*
********************************************************/
void LIS2DH12_ReadXYZACC(uint8_t buff[])
{
   float acceleration_mg[3];
   I2C_ReadBuffer(LIS2DH12_I2C_ADD_L,LIS2DH12_OUT_X_L,data_raw_acceleration.u8bit,6);
   acceleration_mg[0] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[0] );
   acceleration_mg[1] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[1] );
   acceleration_mg[2] = LIS2DH12_FROM_FS_2g_LP_TO_mg( data_raw_acceleration.i16bit[2] );
   buff[0] = (int16_t)acceleration_mg[0];
   buff[1] = ((int16_t)acceleration_mg[0])>>8;
   buff[2] = (int16_t)acceleration_mg[1];
   buff[3] = ((int16_t)acceleration_mg[1])>>8;
   buff[4] = (int16_t)acceleration_mg[2];
   buff[5] = ((int16_t)acceleration_mg[2])>>8;   
}
