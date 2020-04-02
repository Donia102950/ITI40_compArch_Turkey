/*
 * HSwitch_program.c
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */
#include "STD_Types.h"
#include "Hswitch_intertface.h"
#include "HSwitch_Config.h"
#include "GPIO_interface.h"



extern GPIO_t* ptr;

static uint_8t SwitchState[MAX_SWITCH_NUMBER];


extern const Switch_t Switchmap[];

uint_8t HSwitch_GetState(uint_8t Switch_num)
{

	return SwitchState[Switch_num];

}
/*this task should be run every 5 ms*/
void Switch_Runnable(void)
{
	static uint_8t Prev_state[MAX_SWITCH_NUMBER],counter[MAX_SWITCH_NUMBER];
	uint_8t Current_State[MAX_SWITCH_NUMBER],Iterator;

	for (Iterator=0;Iterator<MAX_SWITCH_NUMBER;Iterator++)
	{
		GPIO_u8getValue(ptr,ptr->pin,&Current_State[Iterator]);

		if( Current_State[Iterator]==Prev_state[Iterator])
		{
			counter[Iterator]++;
		}
		else
		{
			counter[Iterator]=0;
		}
		if(counter[Iterator]==5)
		{
			SwitchState[Iterator]=Current_State[Iterator];
		}
		Prev_state[Iterator]=Current_State[Iterator];
	}

}
void HSwitch_Init(void)
{

	GPIO_u8SetConfiguration(ptr);
}
