/*******************************************************************************
* Copyright (c) ManThink Technology Ltd. co.
* All rights reserved. This program and the accompanying materials
* are made available under the software of IAR for ARM version 7.60.2
* This is a demo working with the SDK of LWS made by ManThink Technology
* LWS is a SDK for OM402/OM802 which realize LoRaWAN function.
* The Demo should be run on the hardware of OM402/OM802 produced by ManThink Technology
* http://www.manthink.cn 
* contact info : info@manthink.cn
* contributor  : mingfei zhao
*******************************************************************************/
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
#include "string.h"
#include "MyGlobal.h"

void MT_app_EXTI3_IRQHandler()
{
  /*
  GPIO_IT_Diable(PORTC,3);//disable ptc3 io interrupt
  LLWU->PE2 &= (~LLWU_PE2_WUPE7_MASK);
  PORTC->PCR[3] = (PORTC->PCR[3]&~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(3);//PTC3->LPUART1_RX 
*/   
}
void MT_app_EXTIWK_IRQHandler()
{
}
void MT_app_WKIRQ()
{
    if((SysStatus.Bits.WkIntBits&0x10)==0x10)
    {
        mpos_osfun.DelayUs(2000);
        if(GPIO_PinGet(KEY_GPIO,KEY_PIN)==true) 
        {
                LPInfo.wakingBit.Bits.OnceEvent1=1;
                HookExcuteOnce1 = MT_Tx_Data; 
        }
        SysStatus.Bits.WkIntBits &= ~0x10;
    }
}
void MT_app_GNIRQ()
{
  /*
  if((SysStatus.Bits.WkIntBits&0x40)==0) return;
  SysStatus.Bits.WkIntBits&=0xBF;
*/
}
/*
void MT_app_USART1_IRQHandler()
{
  unsigned int ComSR;
  unsigned char data;
  if(LPUART1->STAT&LPUART_STAT_OR_MASK) { LPUART1->STAT |= LPUART_STAT_OR_MASK; }  
  if(LPUART1->STAT&LPUART_STAT_RDRF_MASK)
  {
        data = LPUART1->DATA;
  }
  else  
  {
        ComSR = LPUART1->DATA;
	LPUART1->STAT |= LPUART1->STAT&(LPUART_STAT_NF_MASK|LPUART_STAT_FE_MASK|LPUART_STAT_PF_MASK|LPUART_STAT_TC_MASK);
  }
}
*/
void MT_app_USART2_IRQHandler()
{
  /*
  unsigned int ComSR;
  unsigned char data;  
  if(UART2->S1&UART_S1_OR_MASK) { ComSR = UART2->D; } 
  if(UART2->S1&UART_S1_RDRF_MASK) 
  {
      data = UART2->D;
      UartBusiness.RxBuf[UartBusiness.RxLenth++]=data; 
      if(UartBusiness.RxLenth>UART_MAX_BUFLEN)
      {
          UartBusiness.RxLenth=0;
      }
      FrameTimeout_Restart(&UartBusiness);
  }
  else  
  {
      ComSR = UART2->D;
      LPUART1->STAT |= LPUART1->STAT&(LPUART_STAT_NF_MASK|LPUART_STAT_FE_MASK|LPUART_STAT_PF_MASK|LPUART_STAT_TC_MASK);
  }
*/
}
