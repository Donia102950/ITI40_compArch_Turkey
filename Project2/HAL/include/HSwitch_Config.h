/*
 * HSwitch_Config.h
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */

#ifndef HSWITCH_CONFIG_H_
#define HSWITCH_CONFIG_H_
#include "STD_Types.h"
#include "GPIO_interface.h"
#define MAX_SWITCH_NUMBER 	 2
/*********************************************************************************************************************/

#define SwitchNumber  1

typedef struct
 {
	GPIO_t Switch;
	uint_8t ID;
 }Switch_t;




#endif /* HSWITCH_CONFIG_H_ */
