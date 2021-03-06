/*********************************************************************************************************************/
/*
 * Author : Mina ,Menna ,Donia ,Hamam ,Nouran
 *
 * Date : 4/2/2020
 *
 * Version : V01
 *
 */
/*********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "Sched.h"
#include "UARTHandler_interface.h"
#include "Hswitch_intertface.h"
#include "HLCD.h"
#include "HLED_Interface.h"
/*********************************************************************************************************************/


/*********************************************************************************************************************/
int main(void)
{
	HSwitch_Init();
	LED_Init();
	LCD_Init();
	HUART_Init();
	Sched_Init();
	Sched_Start();
	return 0;
}
/*********************************************************************************************************************/



