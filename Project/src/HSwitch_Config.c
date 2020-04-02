/*
 * HSwitch_Config.c
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */

#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "Hswitch_intertface.h"
#include "HSwitch_Config.h"

/*typedef struct
{
	 uint_32t      pin;
	 Mode          mode;
	 Speed         speed;
	 uint_8t       port;
}GPIO_t;*/

#define SWITCH_ONE	0
#define SWITCh_TWO	1



const Switch_t Switchmap={.Switch.pin=PIN1,.Switch.mode=MODE_INPUT_INPUTPULLUP,.Switch.speed=SPEED_50MHZ,.Switch.port=PORTA,.ID=SWITCH_ONE};
GPIO_t* ptr =&(Switchmap.Switch);







