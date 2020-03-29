/*
 * HSwitch_Config.c
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */

#include "STD_Types.h"
#include "Hswitch_intertface.h"
#include "HSwitch_Config.h"


#define SWITCH_ONE	0
#define SWITCh_TWO	1

const Switch_t Switchmap[MAX_SWITCH_NUMBER]={
		{SWITCH_ONE,GPIO_PORTA,GPIO_PIN_NUM4},
		{SWITCh_TWO,GPIO_PORTA,GPIO_PIN_NUM3}
};
