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
#include "MyBoard.h"
#include "MyGlobal.h"
#include "MT_KL17_I2C.h"
#include "SHT20.h"
#include "MyAPP.h"

/***********************initialization*************************************************/
void MT_MyBoardInit(void)
{
   /* Init unused GPIO  */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;  
  //GPIO_Config (PORTB, 1, GPIO_Mode_OPP);//PTB1->AUX
  //GPIO_Config (PORTC, 1, GPIO_Mode_OPP);//PTC1
  //GPIO_PinSet( GPIOC, 1, RESET );
  //GPIO_Config (PORTC, 2, GPIO_Mode_OPP);//PTC2
  //GPIO_PinSet( GPIOC, 2, RESET );
  GPIO_Config (PORTC, 5, GPIO_Mode_IPD);//PTC5->
  GPIO_Config (PORTC, 6, GPIO_Mode_IPD);//PTC6->
  //GPIO_Config (PORTC, 7, GPIO_Mode_IPU);//PTC7->SET_A
  GPIO_Config (PORTD, 4, GPIO_Mode_IPD);//PTD4->SET_B
  //GPIO_Config (PORTD, 5, GPIO_Mode_OPP);//PTD5
  GPIO_PinSet( GPIOD, 5, RESET );  
  GPIO_Config (PORTD, 6, GPIO_Mode_OPP);//PTD6
  GPIO_PinSet( GPIOD, 6, RESET );
  //GPIO_Config (PORTD, 7, GPIO_Mode_OPP);//PTD7
  //GPIO_PinSet( GPIOD, 7, RESET );
  GPIO_Config (PORTE, 30, GPIO_Mode_OPP);//PTE30
  GPIO_PinSet( GPIOE, 30, RESET );

  /* Init used GPIO  */
  GPIO_Config(MODULE_AUX_PORT,MODULE_AUX_PIN,GPIO_Mode_OPP); 
  GPIO_PinSet (MODULE_AUX_GPIO, MODULE_AUX_PIN, SET) ;
  GPIO_Config(SHT20_POWER_PORT,SHT20_POWER_PIN,GPIO_Mode_OPP); 
  GPIO_PinSet (SHT20_POWER_GPIO, SHT20_POWER_PIN, SET) ;  
  GPIO_Config(V18B20_POWER_PORT,V18B20_POWER_PIN,GPIO_Mode_OPP); 
  GPIO_PinSet (V18B20_POWER_GPIO, V18B20_POWER_PIN, RESET) ; 
  //Configure IO for KEY to RisingEdge interrupt to upload data
  GPIO_Config (KEY_PORT, KEY_PIN, GPIO_Mode_IPD);
  GPIO_IT_Config(KEY_PORT,KEY_PIN,GPIO_IT_RisingEdge);  
  LLWU->PE3 = (LLWU->PE3&(~LLWU_PE3_WUPE9_MASK))|LLWU_PE3_WUPE9(1);  
  
  I2C_Init();
  MT_Sensor.MPRegister.AlarmStatus.Bits.AccStatus = ~LIS2DH12_Init();//Initial LIS2DH12
}
/********************************************************
* Function for Device_PowerON 
* return: 
*
********************************************************/
void MT_Device_PowerON(void)
{
    //GPIO_PinSet(DEVICE_POWER_GPIO, DEVICE_POWER_PIN, RESET);//Pwoer on device
    //GPIO_PinSet(MODULE_AUX_GPIO, MODULE_AUX_PIN, RESET); //LED==ON
}

void MT_InitUart2(u2_t Baudrate)
{
   mpos_driver.UART2_Init(Baudrate);
}

/********************************************************
* Function for Device_PowerOFF 
* return: 
*
********************************************************/
void MT_Device_PowerOFF(void)
{
    //GPIO_PinSet(DEVICE_POWER_GPIO, DEVICE_POWER_PIN, SET);//Pwoer on device
    //GPIO_PinSet(MODULE_AUX_GPIO, MODULE_AUX_PIN, SET); //LED==OFF
}