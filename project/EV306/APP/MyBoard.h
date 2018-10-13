#ifndef _MY_BOARD_H
#define _MY_BOARD_H
#include "MP_OS.h"
#include "Global.h"
#include "include.h"
//define IO used for meter 
#define SHT20_POWER_PORT	PORTD
#define SHT20_POWER_GPIO	GPIOD
#define SHT20_POWER_PIN         5

#define V18B20_POWER_PORT	PORTC
#define V18B20_POWER_GPIO	GPIOC
#define V18B20_POWER_PIN         7

#define I2C1_SCL_PORT	        PORTC
#define I2C1_SCL_GPIO	        GPIOC
#define I2C1_SCL_PIN            1

#define I2C1_SDA_PORT	        PORTC
#define I2C1_SDA_GPIO	        GPIOC
#define I2C1_SDA_PIN            2

#define UART1_RX_PORT           PORTC
#define UART1_RX_GPIO	        GPIOC
#define UART1_RX_PIN            3

#define MODULE_AUX_PORT	        PORTB
#define MODULE_AUX_GPIO	        GPIOB
#define MODULE_AUX_PIN          1

#define KEY_PORT                PORTC
#define KEY_GPIO	        GPIOC
#define KEY_PIN                 5

#define MT_AUX_LED_ON()       GPIO_PinSet (GPIOB, 1, RESET)//GPIO_PinSet (GPIOD, 7, RESET)
#define MT_AUX_LED_OFF()      GPIO_PinSet (GPIOB, 1, SET)//GPIO_PinSet (GPIOD, 7, SET)

extern void MT_MyBoardInit(void);
extern void MT_Device_PowerON(void);
extern void MT_Device_PowerOFF(void);
#endif