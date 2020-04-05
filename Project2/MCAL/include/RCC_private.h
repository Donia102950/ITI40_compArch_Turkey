/******************************************************************************************/
/*
  Author  : Hammam Mazen
  Date    : 10 March 2020
  Version : V01
*/
/******************************************************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
#include "STD_TYPES.h"
typedef struct
{
	uint_32t CR;
	uint_32t CFGR;
	uint_32t CIR;
	uint_32t APB2RSTR;
	uint_32t APB1RSTR;
	uint_32t AHBENR;
	uint_32t APB2ENR;
	uint_32t APB1ENR;
	uint_32t BDCR;
 	uint_32t CSR;
}RCC_REG;

typedef enum
{
	HSI ,
	HSE ,
	PLL
}myclock;

typedef enum
{
	AHB,
	APB1,
	APB2
}bus;

typedef enum
{
	ON ,
	OFF
}State;

typedef enum
{
	Pre0=0,
	Pre2=2,
	Pre4=4,
	Pre8=8,
	Pre16=16
}APB_Pre;

typedef enum
{
	AHB_Pre0=0,
	AHB_Pre2=2,
	AHB_Pre4=4,
	AHB_Pre8=8,
	AHB_Pre16=16,
	AHB_Pre64=64,
	AHB_Pre128=128,
	AHB_Pre256=256,
	AHB_Pre512=512
}AHB_Pre;
/*********************************************************************************************************************/

#define RCC_BASE_ADDRESS    (0x40021000)
#define RCC                 ((RCC_REG*)0x40021000)
#define HSI_CLK_VALUE      8000000
#define PLL_HSI_VAL        4000000


#define SWS0                                   2
#define SWS1                                   3
#define RCC_CR_PLL_RDY                         25
#define RCC_CR_PLL_ON                          24
#define RCC_CR_CSS_ON                          19
#define RCC_CR_HSE_BYP                         18
#define RCC_CR_HSE_RDY                         17
#define RCC_CR_HSE_ON                          16
#define RCC_CR_HSITRIM0                        3
#define RCC_CR_HSITRIM1                        4
#define RCC_CR_HSITRIM2                        5
#define RCC_CR_HSITRIM3                        6
#define RCC_CR_HSITRIM4                        7
#define RCC_CR_HSICAL0                         8
#define RCC_CR_HSICAL                          19
#define RCC_CR_HSICAL2                         10
#define RCC_CR_HSICAL3                         11
#define RCC_CR_HSICAL4                         12
#define RCC_CR_HSICAL5                         13
#define RCC_CR_HSICAL6                         14
#define RCC_CR_HSICAL7                         15
#define RCC_CR_HSI_RDY                         1
#define RCC_CR_HSI_ON                          0


#define RCC_CFGR_MCO0                          24
#define RCC_CFGR_MCO1                          25
#define RCC_CFGR_MCO2                          26
#define RCC_CFGR_USB_PRE                       22
#define RCC_CFGR_PLL_MUL3                      21
#define RCC_CFGR_PLL_MUL2                      20
#define RCC_CFGR_PLL_MUL1                      19
#define RCC_CFGR_PLL_MUL0                      18
#define RCC_CFGR_PLL_PRE                       17
#define RCC_CFGR_PLL_SRC                       16
#define RCC_CFGR_ADC_PRE0                      14
#define RCC_CFGR_ADC_PRE1                      15
#define RCC_CFGR_PPRE2_2                       13
#define RCC_CFGR_PPRE2_1                       12
#define RCC_CFGR_PPRE2_0                       11
#define RCC_CFGR_PPRE1_2                       10
#define RCC_CFGR_PPRE1_1                       9
#define RCC_CFGR_PPRE1_0                       8
#define RCC_CFGR_HPRE3                         7
#define RCC_CFGR_HPRE2                         6
#define RCC_CFGR_HPRE1                         5
#define RCC_CFGR_HPRE0                         4
#define RCC_CFGR_SWS1                          3
#define RCC_CFGR_SWS0                          2
#define RCC_CFGR_SW1                           1
#define RCC_CFGR_SW0                           0


/*AHB PERIPHERALS*/
#define FSMC_PERIPHERAL                  8
#define CRC_PERIPHERAL                   6
#define FLASH_MEM_INTERFACE_PERIPHERAL   4
#define SRAM_PERIPHERAL                  2
#define DMA2_PERIPHERAL                  1
#define DMA1_PERIPHERAL                  0
#define SDIO_PERIPHERAL                 10

/*AP2 PERIPHERALS*/
#define AFIO_PERIPHERAL                  64
#define PORTA_PERIPHERAL                 66
#define PORTB_PERIPHERAL                 67
#define PORTC_PERIPHERAL                 68
#define PORTD_PERIPHERAL                 69
#define PORTE_PERIPHERAL                 70
#define PORTF_PERIPHERAL                 71
#define PORTG_PERIPHERAL                 72
#define ADC1_PERIPHERAL                  73
#define ADC2_PERIPHERAL                  74
#define TIM1_TIMER_PERIPHERAL            75
#define SPI1_PERIPHERAL                  76
#define TIM8_TIMER_PERIPHERAL            77
#define USART1_PERIPHERAL                78
#define ADC3_PERIPHERAL                  79
#define TIM9_TIME_PERIPHERAL             83
#define TIM10_TIMER_PERIPHERAL           84
#define TIM11_TIMER_PERIPHERAL           85


/*AP1 PERIPHERALS*/
#define TIM2_TIMER_PERIPHERAL            31
#define TIM3_TIMER_PERIPHERAL            32
#define TIM4_TIMER_PERIPHERAL            33
#define TIM5_TIMER_PERIPHERAL            34
#define TIM6_TIMER_PERIPHERAL            35
#define TIM7_TIMER_PERIPHERAL            36
#define TIM12_TIMER_PERIPHERAL           37
#define TIM13_TIMER_PERIPHERAL           38
#define TIM14_TIMER_PERIPHERAL           39
#define WWDGEN_PERIPHERAL                42
#define SPI2_PERIPHERAL                  45
#define SPI3_PERIPHERAL                  46
#define USART2_PERIPHERAL                48
#define USART3_PERIPHERAL                49
#define USART4_PERIPHERAL                50
#define USART5_PERIPHERAL                51
#define I2C1_PERIPHERAL                  52
#define I2C2_PERIPHERAL                  53
#define USB_PERIPHERAL                   54
#define CAN_PERIPHERAL                   56
#define BKPEN_PERIPHERAL                 58
#define PWREN_PERIPHERAL                 59
#define DACEN_PERIPHERAL                 60


/*System clock mask*/
#define SYS_CLOCK_CLEAR_MASK                0xFFFFFFFC
#define HSI_SYS_CLOCK_MASK                  0x00000000
#define HSE_SYS_CLOCK_MASK                  0x00000001
#define PLL_SYS_CLOCK_MASK                  0x00000002

/*CR Register PLLON Bit Set*/

#define PLL_ON_MASK                         0x01000000

/*CR Register CSS Set and Clear mask*/

#define RCC_CR_CSS_SET_MASK                 0x00080000
#define RCC_CR_CSS_CLEAR_MASK               0xFFF7FFFF

/*PLL clock source selection*/

#define RCC_CFGR_PLL_SRC_HSE_MASK           0x00010000
#define RCC_CFGR_PLL_SRC_HSE_DIV_2_MASK     0x00030000
#define RCC_CFGR_PLL_SRC_HSI_MASK           0xFFFCFFFF

/*HSE Types to be configured in HSE_TYPE*/

#define HSE_OSCILLATOR                      1
#define HSE_RC                              2


#define PLL_HSE                             1
#define PLL_HSE_DIV_2                       2
#define PLL_HSI                             3


/*PLL_MUL_MASKS*/
#define PLL_MUL_CLEAR_MASK                  0xFFC3FFFF
#define PLL_MUL_2_MASK                      0x00000000
#define PLL_MUL_3_MASK                      0x00040000
#define PLL_MUL_4_MASK                      0x00080000
#define PLL_MUL_5_MASK                      0x000C0000
#define PLL_MUL_6_MASK                      0x00100000
#define PLL_MUL_7_MASK                      0x00140000
#define PLL_MUL_8_MASK                      0x00180000
#define PLL_MUL_9_MASK                      0x001C0000
#define PLL_MUL_10_MASK                     0x00200000
#define PLL_MUL_11_MASK                     0x00240000
#define PLL_MUL_12_MASK                     0x00280000
#define PLL_MUL_13_MASK                     0x002C0000
#define PLL_MUL_14_MASK                     0x00300000
#define PLL_MUL_15_MASK                     0x00340000
#define PLL_MUL_16_MASK                     0x00380000

/*APB2 Bus Prescaler Masks*/

#define APB2_CLEAR_MASK                     0xFFFFC7FF

#define APB2_NO_PRESCALER_MASK              0x00000000
#define APB2_PRESCALER_2_MASK               0x00002000
#define APB2_PRESCALER_4_MASK               0x00002800
#define APB2_PRESCALER_8_MASK               0x00003000
#define APB2_PRESCALER_16_MASK              0x00003800


/*APB1 Bus Prescaler Masks*/

#define APB1_CLEAR_MASK                     0xFFFFF8FF

#define APB1_NO_PRESCALER_MASK              0x00000000
#define APB1_PRESCALER_2_MASK               0x00000800
#define APB1_PRESCALER_4_MASK               0x00000500
#define APB1_PRESCALER_8_MASK               0x00000600
#define APB1_PRESCALER_16_MASK              0x00000700

/*APB1 Bus Prescaler Masks*/

#define AHB_CLEAR_MASK                      0xFFFFFF0F

#define AHB_NO_PRESCALER_MASK               0x00000000
#define AHB_PRESCALER_2_MASK                0x00000080
#define AHB_PRESCALER_4_MASK                0x00000090
#define AHB_PRESCALER_8_MASK                0x000000A0
#define AHB_PRESCALER_16_MASK               0x000000B0
#define AHB_PRESCALER_64_MASK               0x000000C0
#define AHB_PRESCALER_128_MASK              0x000000D0
#define AHB_PRESCALER_256_MASK              0x000000E0
#define AHB_PRESCALER_512_MASK              0x000000F0


#endif



