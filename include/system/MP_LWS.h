#ifndef _MP_LWS_H_
#define _MP_LWS_H_
#define NEW_VERSION
#include "MP_OS_type.h"
#include "MP_LWS_type.h"
#ifndef _MPOS_RAMLOAD_LIB
extern void     LWS_init (void);
extern void     LoRaWANInit(  );
extern void     LWS_SetRelay(bool status);
extern u4_t     LWS_GetUTCTime(void);
extern u4_t     LWS_GetUPseq(void);
extern void     LWS_SetDeviceTimeReq(void);
extern bool 	SetClassMode(uint8_t classMode);
extern LWERRO_t Join(LWOP_t mode);
extern LWERRO_t JoinReset(LWOP_t mode);
extern LWERRO_t LW_TxData(uint8_t * txBuffer,u1_t lenth,u1_t port,LWOP_t mode);
extern void 	paraFWSetAPPEUI(u1_t* para,u8_t appeui);
extern void 	paraRDSetFreq(u1_t * para, u4_t freq,u1_t band);
extern void 	paraRDSetChannelMap(u1_t * para, u2_t map);
extern void 	paraFWSetDevKey(u1_t *para, u1_t * appkey);
extern void 	paraFWGet(U_CROFW* para);
extern void 	paraRDGet(U_CRORD* para);
extern void 	paraCFGet(U_CROCF * para);
extern void 	paraAPPGet(u1_t * para,u1_t len) ;
extern void 	paraFWSave(U_CROFW * para);
extern void 	paraRDSave(U_CRORD * para);
extern void     paraCFSave(U_CROCF * para);
extern void 	paraAPPSave(u1_t * para,u1_t len);
extern void     paraAPPFlashSave(u1_t * para,u1_t startReg,u1_t len);
extern void 	paraCFmodify(  u1_t Tmode,u1_t SWmode);
#endif
#endif