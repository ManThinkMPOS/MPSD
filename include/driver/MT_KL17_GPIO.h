#ifndef __MT_KL17_GPIO__H
#define __MT_KL17_GPIO__H
#include "MKL17Z644.h"
/**/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) 
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) 

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) 

#define GPIO_MODE             ((uint32_t)0x00000003)
#define EXTI_MODE             ((uint32_t)0x10000000)
#define GPIO_MODE_IT          ((uint32_t)0x00010000)
#define GPIO_MODE_EVT         ((uint32_t)0x00020000)
#define RISING_EDGE           ((uint32_t)0x00100000) 
#define FALLING_EDGE          ((uint32_t)0x00200000) 
#define GPIO_OUTPUT_TYPE      ((uint32_t)0x00000010)



#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入


#define GPIOx(no) ((GPIO_TypeDef*) (GPIOA_BASE + (no)*(GPIOB_BASE-GPIOA_BASE)))

// GPIOCFG macros
#define GPIOCFG_AF_MASK        0x000F
#define GPIOCFG_MODE_SHIFT      4
#define GPIOCFG_MODE_MASK      (3<<GPIOCFG_MODE_SHIFT)
#define GPIOCFG_MODE_INP       (0<<GPIOCFG_MODE_SHIFT)
#define GPIOCFG_MODE_OUT       (1<<GPIOCFG_MODE_SHIFT)
#define GPIOCFG_MODE_ALT       (2<<GPIOCFG_MODE_SHIFT)
#define GPIOCFG_MODE_ANA       (3<<GPIOCFG_MODE_SHIFT)
#define GPIOCFG_OSPEED_SHIFT    6
#define GPIOCFG_OSPEED_MASK    (3<<GPIOCFG_OSPEED_SHIFT)
#define GPIOCFG_OSPEED_400kHz  (0<<GPIOCFG_OSPEED_SHIFT)
#define GPIOCFG_OSPEED_2MHz    (1<<GPIOCFG_OSPEED_SHIFT)
#define GPIOCFG_OSPEED_10MHz   (2<<GPIOCFG_OSPEED_SHIFT)
#define GPIOCFG_OSPEED_40MHz   (3<<GPIOCFG_OSPEED_SHIFT)
#define GPIOCFG_OTYPE_SHIFT     8
#define GPIOCFG_OTYPE_MASK     (1<<GPIOCFG_OTYPE_SHIFT)
#define GPIOCFG_OTYPE_PUPD     (0<<GPIOCFG_OTYPE_SHIFT)
#define GPIOCFG_OTYPE_OPEN     (1<<GPIOCFG_OTYPE_SHIFT)
#define GPIOCFG_PUPD_SHIFT      9
#define GPIOCFG_PUPD_MASK      (3<<GPIOCFG_PUPD_SHIFT)
#define GPIOCFG_PUPD_NONE      (0<<GPIOCFG_PUPD_SHIFT)
#define GPIOCFG_PUPD_PUP       (1<<GPIOCFG_PUPD_SHIFT)
#define GPIOCFG_PUPD_PDN       (2<<GPIOCFG_PUPD_SHIFT)
#define GPIOCFG_PUPD_RFU       (3<<GPIOCFG_PUPD_SHIFT)

// IRQ triggers (same values as in Moterunner!)
#define GPIO_IRQ_MASK          0x38
#define GPIO_IRQ_FALLING       0x20
#define GPIO_IRQ_RISING        0x28
#define GPIO_IRQ_CHANGE        0x30
/*
#define HW_GPIOA  (0x00)
#define HW_GPIOB  (0x01)
#define HW_GPIOC  (0x02)
#define HW_GPIOD  (0x03)
#define HW_GPIOE  (0x04)
*/

typedef enum
{
    GPIO_Mode_IFT = 0x00,       /* Input floating  */
    GPIO_Mode_IPD = 0x01,       /* Pull down input */
    GPIO_Mode_IPU = 0x02,       /* Pull up input    */
    GPIO_Mode_OPP = 0x04,       /* Push pull output */
}GPIO_Mode_Type;
typedef enum
{
    GPIO_IT_Low = 0x08,
    GPIO_IT_RisingEdge = 0x09,
    GPIO_IT_FallingEdge = 0x0A,
    GPIO_IT_RisingFallingEdge = 0x0B,
    GPIO_IT_High= 0x0C,
}GPIO_ITConfig_Type;

extern void GPIO_PinSet (GPIO_Type* gpioport, unsigned char pin, unsigned char state) ;
unsigned char GPIO_PinGet (GPIO_Type* gpioport, unsigned char pin);
void GPIO_PinToggle (GPIO_Type* gpioport, unsigned char pin);
void GPIO_Config (PORT_Type * port, unsigned char pin, GPIO_Mode_Type gpiocfg);
void GPIO_IT_Config(PORT_Type *port,unsigned char pin, GPIO_ITConfig_Type gpiocfg);
void GPIO_IT_Diable(PORT_Type *port,unsigned char pin);
#endif
