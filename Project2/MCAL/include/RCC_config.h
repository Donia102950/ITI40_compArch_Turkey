/******************************************************************************************/
/*
  Author  : Hammam Mazen
  Date    : 10 March 2020
  Version : V01
*/
/******************************************************************************************/
#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H

/* User have to define HSE clock Value here */

#define HSE_CLK_VALUE       16000000
#define PLL_HSE_DIV_2_Value 8000000

#define RCC_CSS             ON
#define PLL_CLK_SOURCE      PLL_HSE

//#define PLL_HSE_DIV_2      ON

/* Choose HSE clock type 1- HSE_OSCILLATOR
 *                       2- HSE_RC          */

#define HSE_TYPE            HSE_OSCILLATOR


#endif
