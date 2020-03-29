/*
 * HSwitch_program.c
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */
#include "STD_Types.h"
#include "Hswitch_intertface.h"
#include "HSwitch_Config.h"
#include "DIO_interface.h"




#define OK 0
#define NOK 1

static u8 SwitchState[MAX_SWITCH_NUMBER];


extern const Switch_t Switchmap[];

u8 HSwitch_GetState(u8 Switch_num)
{

	return SwitchState[Switch_num];

}
/*this task should be run every 5 ms*/
void Switch_Runnable(void)
{
	static u8 Prev_state[MAX_SWITCH_NUMBER],counter[MAX_SWITCH_NUMBER];
	u8 Current_State[MAX_SWITCH_NUMBER],Iterator;

	for (Iterator=0;Iterator<MAX_SWITCH_NUMBER;Iterator++)
	{
		Current_State[Iterator]=DIO_GetPinVal(Switchmap[Iterator].Switch_Port,Switchmap[Iterator].Switch_PinNumber);

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

