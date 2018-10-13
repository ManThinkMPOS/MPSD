#ifndef __LIS2DH12__H
#define __LIS2DH12__H
#include "MKL17Z644.h"

#define ARC_PARA            0.866 // cos30бу

extern int I2C_ReadBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len);
extern int I2C_WriteBuffer(uint8_t chipAddr, uint8_t addr, uint8_t *buf, uint16_t len);
extern u1_t LIS2DH12_Init(void);
extern u1_t LIS2DH12_ReadAcc(void);
extern void LIS2DH12_ReadStatus(void);
extern void LIS2DH12_AngleCheck(void); 
extern void LIS2DH12_LowPower(void);
extern void LIS2DH12_ReadXYZACC(uint8_t buff[]);
#endif