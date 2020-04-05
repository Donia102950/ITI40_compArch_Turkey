/******************************************************************************************/
/*
  Author  : Hammam Mazen
  Date    : 10 March 2020
  Version : V01
*/
/******************************************************************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H
#include "RCC_private.h"

/* RCC_ErrSysClk Function is used to set System Clock with its value
 *Inputs :
 * Set Clk : 1- HSI
 * 			 2- HSE
 * 			 3- PLL
 * 	   Clock_Value: System Clock must be less than 72 MHZ
 *Reutrn : StdError */

StdError RCC_ErrSysClk(myclock Clk,uint_32t Clock_Value);
/*********************************************************************************************************************/

/*RCC_u8GetClockSource function is used to get which clock is use as system clock
 * Input : Void
 * Return : 0 -> HSI
 * 			1 -> HSE
 * 			2 -> PLL */

uint_8t RCC_u8GetClockSource(void);
/*********************************************************************************************************************/

/* RCC_voidEnPeriClk function is used to Enable peripheral clock
 * Input: peripheral name
 * Return : StdError*/

StdError RCC_voidEnPeriClk(uint_8t Peripheral);
/*********************************************************************************************************************/

/* RCC_voidDisPeriClk function is used to Enable peripheral clock
 * Input: peripheral name
 * Return : StdError*/

StdError RCC_voidDisPeriClk(uint_8t Peripheral);
/*********************************************************************************************************************/

/* RCC_u32GetSysClkValue function is used to get value of system clock in HZ */

uint_32t RCC_u32GetSysClkValue(void);
/*********************************************************************************************************************/

/* RCC_u32GetAHBClkValue function is used to get value of AHB bus clock in HZ */

uint_32t RCC_u32GetAHBClkValue(void);
/*********************************************************************************************************************/

/* APB2_Divider function is used to set a prescaler for APB2 Bus
 * **Prescaler Values are  0,2,4,8,16 */

StdError APB2_Divider(APB_Pre Prescaler);
/*********************************************************************************************************************/

/* APB1_Divider function is used to set a prescaler for APB2 Bus
 * Input: Prescaler Values are  0,2,4,8,16
 * Return : StdError */

StdError APB1_Divider(APB_Pre Prescaler);
/*********************************************************************************************************************/

/* AHB_Divider function is used to set a peascaler for APB2 Bus
 * Input: Prescaler Values are  0,2,4,8,16,64,128,256,512
 * Return : StdError */
StdError AHB_Divider(AHB_Pre Prescaler);


#endif


