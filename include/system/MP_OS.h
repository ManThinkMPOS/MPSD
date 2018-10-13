#ifndef _MP_OS_H_
#define _MP_OS_H_
#include "stdio.h"
#include "include.h"
#include "MP_OS_type.h"
#include "MP_LWS_type.h"
  

//API hook function of interrupt
extern  void (* HOOK_EXTI1_IRQHandler)(void) ;
extern  void (* HOOK_EXTI0_IRQHandler)(void) ;
extern  void (* HOOK_EXTI3_IRQHandler)(void);
extern  void (* HOOK_EXTIWK_IRQHandler)(void);
extern  void (* HOOK_EXTIPORTBCDE_WKIRQHandler)(void);
extern  void (* HOOK_EXTIPORTBCDE_GNIRQHandler)(void);
extern  void (*	HOOK_USART1_IRQHandler)(void);
extern  void (*	HOOK_USART2_IRQHandler)(void);
extern  void (*	HOOK_RTC_IRQHandler)(void);
extern  void (* HOOK_LPTIM_IRQHandler)(void);
extern void (* HookAPPParaChanged)(u1_t * paras);
extern void (* mp_userInit)(void);
extern bool ( *HookUserCheck)( void );

extern void (* HookExcuteOnce1)();                             
extern void (* HookExcuteOnce2)();                              
extern void (* HookExcuteOnce3)();                             
#ifndef _MPOS_RAMLOAD_LIB
extern void enableInterrupts();
extern void disableInterrupts();
extern void Clock_Init(void);
extern void IWdgInit();
extern void Hal_Init(void);       
extern void SysParaInit(void);
extern bool PTaskInit(u1_t TaskNO,void ( *callback )( void ), uint32_t timeout );
extern bool PTaskStart(u1_t TaskNO);
extern bool PTaskStop(u1_t TaskNO);
extern bool PTaskIsRuning(u1_t TaskNO);

extern void Task_sem_init(SEMPHORE * mysem, int counts);
extern void Task_sem_release(SEMPHORE * mysem);
extern bool Task_sem_waitOne(S_periodTask * task, SEMPHORE * mysem,s8_t waitTime);
extern void TaskSetPeriod(S_periodTask * task,s8_t period);
extern void TaskExcuteNow(S_periodTask * task);
extern void TaskRestart(S_periodTask * task);
extern void TaskSetup(S_periodTask * task);
extern void TaskRemove(S_periodTask * task);
extern void TaskStop(S_periodTask * task);


extern void Flash_SizeSelect(uint16_t size);
extern u4_t LWS_GetUTCTime();
extern uint8_t  ADC_GetVoltageValue(void);
extern uint8_t  ADC_GetTempValue(void);
extern void paraAPPGet(u1_t * para,u1_t len) ;
extern void paraAPPSave(u1_t * para,u1_t len);
extern u1_t ADC_GetTempValue(void);
extern u1_t ADC_GetVoltageValue(void);
extern void memcpy1( uint8_t *dst, uint8_t *src, uint16_t size );
extern u2_t os_rlsbf2 (u1_t * buf);
extern u4_t os_rlsbf4 (u1_t * buf);
extern u8_t os_rlsbf8 (u1_t * buf) ;
extern uint16_t  CUSUM_CRC(uint8_t *buf,uint16_t lenth);
extern u2_t mp_modeACRC(unsigned char *buf,unsigned int lenth,u2_t poly);
extern u2_t mp_modeBCRC (u1_t * data, u2_t len,u2_t poly);
extern u2_t os_crc16 (u1_t * data, u2_t len);
extern uint8_t crc8_ccit(const uint8_t * data, unsigned size); 
extern void DelayUs(unsigned long nCount);
#endif
#endif
