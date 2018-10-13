#ifndef __MP_LWS_TYPE__H
#define __MP_LWS_TYPE__H
#include "MKL17Z644.h"
#define CLASS_A 0x01
#define CLASS_B 0x02
#define CLASS_C 0x00
#define CLASS_D 0x03
enum _ev_t { EV_SCAN_TIMEOUT=1, EV_BEACON_FOUND,
             EV_BEACON_MISSED, EV_BEACON_TRACKED, EV_JOINING,
             EV_JOINED, EV_RFU1, EV_JOIN_FAILED, EV_REJOIN_FAILED,
             EV_TXCOMPLETE, EV_TXOVER_NACK,EV_TXOVER_NOPORT,EV_TXOVER_DNW1,EV_TXOVER_DNW2,EV_PING_MAC_PORT,EV_TXOVER_PING,
             EV_LOST_TSYNC, EV_RESET,
             EV_RXCOMPLETE,EV_SWRXDONE,EV_LINK_DEAD, EV_LINK_ALIVE,EV_TXDONE,EV_MICWRONG,EV_MODE_CHGOK,EV_MODE_CHGFAIL,
             EV_TXCOMPLETE_INT,EV_TXOVER_MAC_NOPORT,EV_TXOVER_MAC_PORT,EV_NTRX,EV_BCN_GWCHG,};
typedef enum _ev_t ev_t;
enum _LWoperate_t { LWOP_JOIN=1, LWOP_REJOIN,LWOP_LTC,LWOP_LTU,LWOP_SWT };
typedef enum _LWoperate_t LWOP_t;
enum _LWErro_t { LW_OK=0, LW_ERRO_ACTIVED=1, LW_ERRO_BUSY,LW_ERRO_NOKEY,LW_ERRO_UNACTIVED ,LW_ERRO_NOCHAN ,LW_ERRO_INVALID};
typedef enum _LWErro_t LWERRO_t;
enum _mt_ev_t { MT_EV_SCAN_TIMEOUT=1, MT_EV_BEACON_FOUND,
MT_EV_BEACON_MISSED, MT_EV_BEACON_TRACKED, MT_EV_JOINING,
MT_EV_JOINED, MT_EV_RFU1, MT_EV_JOIN_FAILED, MT_EV_REJOIN_FAILED,
MT_EV_TXCOMPLETE, MT_EV_TXOVER_NACK,MT_EV_TXOVER_NOPORT,MT_EV_TXOVER_DNW1,MT_EV_TXOVER_DNW2,MT_EV_PING_MAC_PORT,MT_EV_TXOVER_PING,
MT_EV_LOST_TSYNC, MT_EV_RESET,
MT_EV_RXCOMPLETE,MT_EV_SWRXDONE, MT_EV_LINK_DEAD, MT_EV_LINK_ALIVE,MT_EV_TXDONE,MT_EV_MICWRONG,MT_EV_MODE_CHGOK,MT_EV_MODE_CHGFAIL,
MT_EV_TXCOMPLETE_INT,MT_EV_TXOVER_MAC_NOPORT,MT_EV_TXOVER_MAC_PORT,MT_EV_NTRX,MT_EV_BCN_GWCHG,};
typedef enum _mt_ev_t mt_ev_t;
typedef enum
{
    MODEM_FSK = 0,
    MODEM_LORA,
}RadioModems_t;
typedef struct 
{
	RadioModems_t modem;
	int8_t power;
	uint32_t fdev; 
	uint32_t bandwidthAfc;
        uint32_t bw;
	uint32_t sf;
        uint8_t coderate;
	uint16_t preambleLen;
	uint16_t symbTimeout;
	bool fixLen;
	uint8_t  PayloadLen;
	bool crcOn;
	bool freqHopOn;
	uint8_t hopPeriod;
	bool iqInverted;
	bool rxContinuous;
} RadioConfig_t;
typedef struct t_CRO_FW
{
  unsigned char MType;
  unsigned char HwVersion;
  unsigned char FmVersion;
  unsigned char DevEui[8];
  unsigned char AppEui[8];
  unsigned char DevAddr[4];
  unsigned char NetID[4];
  unsigned char NwkSKey[16];
  unsigned char APPSKey[16];
  unsigned char DevKey[16];	
  unsigned char RxWinDelay1;
  unsigned char RxWinDelay2;
  unsigned char JoinDelay1;
  unsigned char JoinDelay2;
  unsigned char ReTx;
  unsigned char globalDutyRate;
  unsigned char DutyBand[4][2]; 
  unsigned char DevTimeReqDuty;
} PACKED T_CRO_FW;
typedef union U_CRO_FW
{
  T_CRO_FW SFwRegister;
  unsigned char Bytes[91];
} PACKED U_CROFW;
typedef union
{
  unsigned char ByteS;
  struct
  {
    unsigned char LoDr  :4;
    unsigned char HiDr :4;
  } PACKED Bits;
} PACKED U_DRRAN;

typedef struct s_FreqDR
{
  unsigned char SFreq[4];
  U_DRRAN DRRange;
} PACKED S_FREQDR;
typedef struct t_CRO_RD
{
  unsigned char   dn2Freq[4];
  unsigned char   dn2Dr;
  unsigned char  	channelMap[2];
  unsigned char 	Power;
  S_FREQDR 		Freq[16];
  u2_t aliCHcntl;
}PACKED T_CRO_RD;
typedef union u_CRO_RD
{
  T_CRO_RD SRdRegister;
  unsigned char Bytes[90]; 
}PACKED U_CRORD;

typedef union
{
  u2_t ByteS;
  struct
  {
    u2_t window1Enable :1;
    u2_t window2Enable :1;
    u2_t MulPingEnable :1;
    u2_t SleepWakeEnable:1;
    u2_t Standard:4;
    u2_t Tmode:1;
    u2_t RssiEnable:1;
    u2_t SNREnable:1;
    u2_t RelayEnable:1;
    u2_t DwellTime:1;
    u2_t aliLowDR:1;
    u2_t Reserved  :2;
  } PACKED Bits;
}  U_EXSTACKCNF;
typedef union
{
  u1_t ByteS;
  struct
  {
    u1_t MaxEIRP :4;
    u1_t UplinkDwellTime :1;
    u1_t DownlinkDwellTime :1;
    u1_t RFU:2;
  } PACKED Bits;
}  U_MAXDWELLTIME;
typedef struct t_CRO_CF
{
	U_EXSTACKCNF    exStackFunction;
	unsigned char   MulDevAddr[4];
	unsigned char   MulNSessionKey[16];
	unsigned char   MulASessionKey[16];
        unsigned char   BeaconFreq[4];
	unsigned char   BeaconDR;
        unsigned char   BeaconPeriod;
	unsigned char   BeaconAirTime[4];
	unsigned char   pingFreq[4];
	unsigned char   pingDR;
	unsigned char   pingIntvExp;
	unsigned char   MulPingFreq[4];
	unsigned char   MulPingDR;
	unsigned char   MulPingIntvExp;
	unsigned char   SWSF;
	unsigned char   SWBW;
	unsigned char   SWFreq[4];
	unsigned char   SWPeriod;
	unsigned char   uprepeat;
	unsigned char   JoinCHMap[2];
	unsigned char   DRRange;
	unsigned char   RelayWin2;
	unsigned char   RelayFreqMap[2];
	unsigned char	RelayDR;
	unsigned char   RelayPeriod;
	unsigned char   RelayDelayTx;
	U_MAXDWELLTIME   MaxDwellTime;
}PACKED T_CRO_CF;

typedef union U_CRO_CF
{
	T_CRO_CF CFRegister;
	unsigned char Bytes[82];
}PACKED U_CROCF;

/////////////For Big endian
typedef union
{
  u2_t ByteS;
  struct
  {
    u2_t Mode :2;
    u2_t ADR  :1;
    u2_t OTA  :1;
    u2_t LinkCheck  :1;
    u2_t FDD :1;
    u2_t ServerADR  :1;
    u2_t DeviceReset:1; //only write, read=0
    u2_t JoinStatus :1;
    u2_t StackState :3;
    u2_t LastTxState:1; //
    u2_t Pending    :1; // 
    u2_t NOTClassA	:1;
    u2_t Reserved  :1; 
  } PACKED Bits;
}  U_STATE;
typedef union
{
  u2_t ByteS;
  struct
  {
    u2_t linkcheckReq   :1;
    u2_t DeviceTimeReq  :1;
	u2_t pingInfoReq:1;
    u2_t Reserved  :13; 
  } PACKED Bits;
}  U_MACREQ;

typedef struct s_CNO
{
  U_STATE State;
  unsigned char DR;
  unsigned char BattLevel;
  unsigned char RetryCounts;
  unsigned char RSSI;
  signed char   SNR;
  unsigned char ChanIndex;
  unsigned char RxSlot;
  unsigned char Reserved;
  U_MACREQ macReq;
  u4_t DeviceTime;
  u1_t linkmargin;
  u1_t linkgwcount;
  
}PACKED SCNO;
typedef union U_CNO_
{
  SCNO Varible;
  unsigned char Bytes[18];
} PACKED U_RunStatus;
typedef struct t_ram_fun_lws
{
  void (*LWS_init) (void);
  void (*LoRaWANInit)();
  void (*LWS_SetDR)(unsigned char DR);
  void (*LWS_SetFDD)(unsigned char status);
  void (*LWS_SetADR)(unsigned char status);
  void (*LWS_SetServerADR)(unsigned char status);
  void (*LWS_SetLinkCheck)(unsigned char status);
  void (*LWS_SetRelay)(bool status);
  u4_t (*LWS_GetUTCTime)(void);
  u4_t (*LWS_GetUPseq)(void);
  void (*LWS_SetDeviceTimeReq)(void);
  bool 	(*LWS_SetClassMode)(uint8_t classMode);
  LWERRO_t (*Join)(LWOP_t mode);
  LWERRO_t (*JoinReset)(LWOP_t mode);
  LWERRO_t (*LW_TxData)(uint8_t * txBuffer,u1_t lenth,u1_t port,LWOP_t mode);
  void 	(*paraFWSetAPPEUI)(u1_t* para,u8_t appeui);
  void 	(*paraRDSetFreq)(u1_t * para, u4_t freq,u1_t band);
  void 	(*paraRDSetChannelMap)(u1_t * para, u2_t map);
  void 	(*paraFWSetDevKey)(u1_t *para, u1_t * appkey);
  void 	(*paraFWGet)(U_CROFW* para);
  void 	(*paraRDGet)(U_CRORD* para);
  void 	(*paraCFGet)(U_CROCF * para);
  void 	(*paraAPPGet)(u1_t * para,u1_t len) ;
  void 	(*paraFWSave)(U_CROFW * para);
  void 	(*paraRDSave)(U_CRORD * para);
  void  (*paraCFSave)(U_CROCF * para);
  void 	(*paraAPPSave)(u1_t * para,u1_t len);
  void  (*paraAPPFlashSave)(u1_t * para,u1_t startReg,u1_t len);
  void 	(*paraCFmodify)(  u1_t Tmode,u1_t SWmode);
  void ( *resv[16] )( void );  
  unsigned char (*lws_relayupinstall)(u1_t * buffer,u1_t size);
  void (*lws_relaydnInstall)(u1_t * buffer,u1_t size);
  void (*lws_RelayToEnd)(u1_t index);
  void (*lws_RelayToEnd1)();
  void (*lws_RelayToEnd2)();
  void (*lws_RelayToEnd3)();
  void (*lws_RelayInit)();
}T_MP_FUN_LWS;

#endif
