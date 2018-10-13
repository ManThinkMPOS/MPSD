#ifndef __MP_OS_TYPE__H
#define __MP_OS_TYPE__H
#include "MKL17Z644.h"
#include "MT_KL17_GPIO.h"
#include "MP_LWS_type.h"
#define CRO_FW        0x01
#define CRO_RD		  0x02
#define CIO_WM        0x03  //working mode
#define CNO_DS		  0x04 //Device Status
#define CCP_LJ        0x05
#define CCP_JR        0x06 //join reset
#define CCP_LTC		  0x07
#define CCP_LTU       0x08
#define CRO_CF		  0x09
#define CCP_TX		  0x0A //TX data when sleep wakeup mode

#define EV_LJ		  0x10
#define EV_LT         0x11
#define EV_LINK       0x12
#define EV_MODSWITCH  0x13  // result of mode change

#define EV_NTRX	  	  0x14	//rx over when pinging, no transmitte but get down data, ClassB/ClassC/ClassD
#define EV_SWRX		  0x15  // rx over when module is sleep to wakeup mode
#define EV_BCNLOST	  0x16	//beacon lost when tracking

#define EV_BCNF		  0x17	//beacon found when finding
#define EV_BCNM		  0x18	//beacon missed when tracking
#define EV_BCNG		  0x19	//beacon got when tracking
#define EV_TOUT		  0x1A	//no beacon found when finding
#define T_DEBUG		  0x1B
#define T_USER		  0x1C
#define CRO_SP		  0x1E
#define EV_TEST       0x1F


#define FLASH_RD	0
#define FLASH_WR	1

#define  POLY 0xa001


#define FRM_HEAD1 0xFF
#define FRM_HEAD2 0xAA
#define FRM_END   0x40

#define FRM_PAYLEN_NO   0x03
#define FRM_PAY_NO  	0x04 //
#define FRM_INFO_LEN 	0x07//


#define FRM_OK       		0x00
#define FRM_ERRO_FRM 		0x01 //
#define FRM_ERRO_CRC 		0x02  //
#define FRM_ERRO_CMD 		0x03  //
#define FRM_ERRO_ADDR 		0x04 //
#define FRM_ERRO_REGLen 	0x05 //

#define FRM_ERRO_INVALID 	0x06//
#define FRM_ERRO_BUSY    	0x07
#define T_ERRO_NOCHAN    	0x08
#define T_ERRO_NOKEY   		0x09
#define JOIN_ERRO_ACTIVED 	0x0A 
#define T_ERRO_UNACTIVED            0x0B
#define T_ERRO_INT		0x0C
#define JOIN_ERRO_DEN     	0x11
#define T_EERO_FAIL      	0x12
#define T_OK_TRX        	0x13
#define T_OK_RXPEND         0x14 //

#define NT_OK_UNI			0x15
#define NT_OK_MUL			0x16

#define MDSWCH_OK			0x17
#define MDSWCH_FAIL			0x18
#define MDSWCH_FAIL_BCNMISS 0x19
#define MDSWCH_FAIL_SCANTIMOUT 0x1A
#define MDSWCH_FAIL_LOSTSYN 0x1B

#define NT_OK_SW			0x20

#define LINK_ALIVE      	0x31
#define LINK_DEAD       	0x32
#define LINK_ERRO_MIC   	0x33

#define PORT_SWINTER		220
#define PORT_SWEX		215
#define PORT_SUCESS		211
#define PORT_FAILED		212

#ifndef NULL
#define NULL       ( ( void * )0 )
#endif
#ifndef SUCCESS
#define SUCCESS                                     1
#endif
#ifndef FAIL
#define FAIL                                        0  
#endif 
typedef s8_t  mp_ostime_t;
struct timer {
  mp_ostime_t start;
  mp_ostime_t interval;
};
typedef struct MPthread_s
{
    uint32_t Timestamp;         
    uint32_t ReloadValue;       
    bool IsRunning;             
    void ( *Callback )( void ); 
    struct MPthread_s *Next;  
}MP_Thread_t;

typedef u2_t SEMPHORE;
typedef union
  {
    u1_t Byte;
    struct
    {
      u1_t enable:1;
      u1_t reserved:7;
    }
  PACKED  Bits;
}PACKED U_SEM_STAT; // added by zhaomingfei 2016
typedef struct
{
  U_SEM_STAT  sembit;
  mp_ostime_t Shadowinterval; //ms
} PACKED S_SEM;
typedef struct periodTask
{
  void ( *Task )( void * task, void * para ); //! Timer IRQ callback function
  mp_ostime_t interval; //ms
  u4_t cycles;
  void (*HookSleep)(void);
  void (*HookWake)(void);
  struct timer period;
  struct periodTask *next;
  void * para;
  S_SEM seminfo;
}PACKED S_periodTask;
typedef struct hook_Event
{
  void (* function)( mt_ev_t ev ,u1_t port,u1_t * Buffer, u2_t len);
  mt_ev_t event;
  u1_t port;
  u1_t * buffer;
  u2_t len;
} S_HookEvent;
typedef struct t_mp_controlBit
{
	u4_t MacAllow:1;
	u4_t actived:1;
	u4_t rsv:30;
} PACKED T_MP_CONTRL_BIT;
typedef struct t_LWSFunction
{
  bool nosleep;
  bool watchdog;
  bool uart1;
  bool lorawan;
  bool MTprotocol;
  bool FlashBackup;
  uint32_t FlashParaADDR; //used to save the parameters of LoRaWAN
  uint32_t FlashParaBackupADDR;
  uint32_t FlashDataBaseADDR;
}PACKED TLWSFUC;
typedef struct t_ModModel
{
  unsigned int     ModeBusDelay;//
  unsigned int     RxLenth;     //
  unsigned int     TxLenth;	//
  unsigned int     TxNumber;  //
  unsigned char    ModBufferRx[280];
  unsigned char    ModBufferUART[280]; //
} PACKED TMODMODEL;

typedef union  uAPPSTATUS
{
	u2_t ByteS;
	struct 
	{
		u2_t fieldMode:1;
		u2_t Reserved:15;
	} PACKED Bits;
} U_APP_STATUS;
typedef union uCROAPP
{
	u1_t ByteS[255];
	struct
	{
		U_APP_STATUS appstatus;
		u1_t userPara[253];
	} PACKED paras;
} U_CRO_APP;

typedef union
{
  u1_t ByteS;
  struct
  {
    u1_t ControlCode :5; 
    u1_t Status :1; //1=sucess 0=failed
    u1_t Operate :1;//1=write 0=read
    u1_t Direction :1;	//1=From Host 0=From This module	
  } PACKED Bits;
} PACKED U_Command;
typedef struct 
{
  u1_t Header[2];
  U_Command Command;
  u1_t Lenth;
} PACKED S_PHeader;
typedef union
{
  u4_t ByteS;
  struct
  {
    u4_t StackEvent :1; 
    u4_t WindowCacu:1;
    u4_t CystalCacuR:1;
    u4_t RTCCacu:1;
    u4_t FirstCacuR:1;
    u4_t KeyUpdate:1;
    u4_t DnSeqUpdate:1;
    u4_t ClassBrejoinFlag:1;
    u4_t WkIntBits:8;
    u4_t InterfaceMode:2;
    u4_t LoraWanBusy:1;
    u4_t RelayStatus:1;
    u4_t InterruptExcuate:8;
    u4_t Reserved:4;
  } PACKED Bits;
} PACKED U_SYSSTATUS;
typedef union
{
  u1_t ByteS;
  struct
  {
    u1_t WakeUpMode:3;
	u1_t reserved1:1;//LowPower:1; //For interrupt
	u1_t reserved2:1;//EnableSleep:1;
	u1_t reserved3:2;//SleepMode:2;
	u1_t reserved4:1;//EnableTIMSleep:1;
  }
  PACKED  Bits;
}PACKED U_LOWPOWERCON;
typedef union
{
  u2_t ByteS;
  struct
  {
    u2_t UARTRX:1; //For interrupt
    u2_t UARTTX:1;
    u2_t Reserverd:3;
	u2_t OnceEvent:1; //defined for the protocol stack
    u2_t Event:1;
    u2_t UserEvent:1; //defined by the user to define any other event, just like, if a user want to realize a interrupt to get the AD value , user should set this bit, and reset this bit after it's event
	u2_t OnceEvent1:1; //defined by the user
	u2_t OnceEvent2:1;//defined by the user
	u2_t OnceEvent3:1;//defined by the user
    u2_t RFU:5;
  }
  PACKED  Bits;
}PACKED U_WAKINGBITS; // added by zhaomingfei 2016
typedef union
{
  u2_t ByteS;
  struct
  {
    u2_t RFTXING:1;
    u2_t RFRXING:1;
    u2_t RFCADING:1;
    u2_t Tmode:1;
    u2_t OnceEvent:1; //defined for the protocol stack
    u2_t Event:1;
    u2_t UserEvent:1; //defined by the user to define any other event, just like, if a user want to realize a interrupt to get the AD value , user should set this bit, and reset this bit after it's event
    u2_t RFU:9;
  }
  PACKED  Bits;
}PACKED U_LIGHT_WAKINGBITS; // added by zhaomingfei 2016

typedef struct
{
  U_WAKINGBITS  		wakingBit;// added by zhaomingfei 2016
  U_LIGHT_WAKINGBITS 	lightWakingBit;
  U_LOWPOWERCON 		ControlBit;
  u2_t          		SleepCounts;
  u2_t          		WdCounter;
  bool 		    		lptimupdatestatus;
  mp_ostime_t   		updatecnt;	
} PACKED S_LPINFO;

typedef struct t_RTC_Datetime
{
    uint16_t year;  /*!< Range from 1970 to 2099.*/
    uint8_t month;  /*!< Range from 1 to 12.*/
    uint8_t day;    /*!< Range from 1 to 31 (depending on month).*/
    uint8_t hour;   /*!< Range from 0 to 23.*/
    uint8_t minute; /*!< Range from 0 to 59.*/
    uint8_t second; /*!< Range from 0 to 59.*/
    uint32_t UTC_Second;
    uint32_t UTC_MicSec;
}PACKED T_RTC_DATETIME;
typedef struct t_ram_fun_driver
{
  void (*mcureset)(void);
  void (*kickdog)(void);
  void (*Clock_Init)(void);
  unsigned char (*Database_Read)(u4_t Addr,u1_t *RxBuffer,u2_t Length);
  unsigned char (*Database_Write)(u4_t Addr,uint8_t *RxBuffer,u2_t Length);
  unsigned char (*Database_USR_Read)(u4_t rawADDR,u4_t backupADDR,u1_t index,u4_t Addr,u1_t *RxBuffer,u2_t Length)  ; 
  unsigned char (*Database_USR_Write)(u4_t rawADDR,u4_t backupADDR,u1_t index,u4_t Addr,u1_t *RxBuffer,u2_t Length);
  unsigned char (*Flash_FreeWrite)(uint32_t Addr,uint8_t *RxBuffer,uint16_t Length);
  unsigned char (*Flash_FreeRead)(uint32_t Addr,uint8_t *RxBuffer,uint16_t Length) ;
  uint8_t (*ADC_GetTempValue)(void);
  void (*GPIO_PinSet) (GPIO_Type* gpioport, unsigned char pin, unsigned char state) ;
  unsigned char (*GPIO_PinGet )(GPIO_Type* gpioport, unsigned char pin);
  void (*GPIO_Config) (PORT_Type * port, unsigned char pin, GPIO_Mode_Type gpiocfg);
  void (*GPIO_IT_Config)(PORT_Type *port,unsigned char pin, GPIO_ITConfig_Type gpiocfg);
  void (*GPIO_IT_Diable)(PORT_Type *port,unsigned char pin);
  void (*RTC_ConvertSecondsToDatetime)(uint32_t seconds, T_RTC_DATETIME *datetime);
  uint32_t (*RTC_ConvertDatetimeToSeconds)(T_RTC_DATETIME *datetime);
  void (*RTC_SetDatetime)(T_RTC_DATETIME *datetime);
  void (*RTC_GetDatetime)(T_RTC_DATETIME *datetime);
  uint32_t (*RTC_GetSencond)(void);
  void (*RTC_SetSencond)(uint32_t second);
  void (*RTC_SetAlarm)(uint32_t interval);
  void (*Spi_Init)(SPI_Type* SPIx);
  unsigned char (*SpiInOut)(SPI_Type* SPIx,unsigned char outData);
  void (*SPI_Cmd)(SPI_Type* SPIx,FunctionalState NewState);
  void (*UART1_Init)(uint32_t baudrate);
  unsigned char (*UART1_SendBuffer)(unsigned char* data,unsigned short len); //
  void (*UART2_Init)(uint32_t baudrate);
  unsigned char (*UART2_SendBuffer)(unsigned char* data,unsigned short len); //
  void ( *resv[16] )( void ); 
}T_MP_FUN_DRIVER;

typedef struct t_ram_fun_os
{
  void (*enableInterrupts)();
  void (*disableInterrupts)();
  void (*SysParaInit)(); // parameters in flash.
  void (*DelayUs)(unsigned long nCount) ;
  void (*Task_Setup)(S_periodTask * task);
  void (*Task_SetPeriod)(S_periodTask * task,s8_t period);
  void (*Task_Restart)(S_periodTask * task);
  void (*Task_ExcuteNow)(S_periodTask * task);
  void (*Task_Stop)(S_periodTask * task);
  void (*Task_Remove)(S_periodTask * task);

  void (*Task_sem_init)(SEMPHORE * mysem, int counts);
  void (*Task_sem_release)(SEMPHORE * mysem);
  bool (*Task_sem_waitOne)(S_periodTask * task, SEMPHORE * mysem,s8_t waitTime);
  bool (*PTaskInit)(u1_t TaskNO,void ( *callback )( void ), uint32_t timeout );
  bool (*PTaskStart)(u1_t TaskNO);
  bool (*PTaskStop)(u1_t TaskNO);
  bool (*PTaskIsRuning)(u1_t TaskNO);
  void ( *resv[16] )( void ); 
  void (*memcpy1)( uint8_t *dst, uint8_t *src, uint16_t size );
  u2_t (*os_rlsbf2) (u1_t * buf);
  u4_t (*os_rlsbf4) (u1_t * buf);
  u4_t (*os_rmsbf4) (u1_t * buf);
  u8_t (*os_rlsbf8) (u1_t * buf) ;
  void (*os_wlsbf2) (u1_t * buf, u2_t v);
  void (*os_wlsbf3) (u1_t * buf, u4_t v);
  void (*os_wlsbf4) (u1_t * buf, u4_t v);
  void (*os_wlsbf8) (u1_t * buf, u8_t v);
  void (*os_wmsbf3) (u1_t * buf, u4_t v) ;
  void (*os_wmsbf4) (u1_t * buf, u4_t v);
  u2_t (*mp_modeACRC)(unsigned char *buf,unsigned int lenth,u2_t poly);
  uint8_t (*crc8_ccit)(const uint8_t * data, unsigned size); 
  uint16_t(* CUSUM_CRC)(uint8_t *buf,uint16_t lenth);
}T_MP_FUN_OS;
#endif
