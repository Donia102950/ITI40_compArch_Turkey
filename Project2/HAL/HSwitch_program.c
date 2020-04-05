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
#include "Sched.h"

/*********************************************************************************************************************/
void Switch_Runnable(void);


//extern GPIO_t* ptr;
extern Switch_t Switchmap[SwitchNumber];
static uint_8t SwitchState[MAX_SWITCH_NUMBER];

task_t SwitchTask;

/*********************************************************************************************************************/

uint_8t HSwitch_GetState(uint_8t Switch_num)
{

	return SwitchState[Switch_num];

}
/*********************************************************************************************************************/

/*this task should be run every 5 ms*/
void Switch_Runnable(void)
{
	static uint_8t Prev_state[MAX_SWITCH_NUMBER],counter[MAX_SWITCH_NUMBER];
	uint_8t Current_State[MAX_SWITCH_NUMBER],Iterator;

	for (Iterator=0;Iterator<MAX_SWITCH_NUMBER;Iterator++)
	{
		GPIO_u8getValue(&(Switchmap[Iterator].Switch),Switchmap[Iterator].Switch.pin,&Current_State[Iterator]);

		if( Current_State[Iterator]==Prev_state[Iterator])
		{
			counter[Iterator]++;
		}
		else
		{
			counter[Iterator]=0;
		}
		if(counter[Iterator]==5)/*25ms dev tick time */
		{
			SwitchState[Iterator]=Current_State[Iterator];
		}
		Prev_state[Iterator]=Current_State[Iterator];
	}

}
/*********************************************************************************************************************/

void HSwitch_Init(void)
{
	uint_8t Iterator;
	SwitchTask.Runnable=Switch_Runnable;
	SwitchTask.periodicity=5;						/*macro*/
	for (Iterator=0;Iterator<MAX_SWITCH_NUMBER;Iterator++)
	{
		GPIO_u8SetConfiguration(&(Switchmap[Iterator].Switch));
	}
}
