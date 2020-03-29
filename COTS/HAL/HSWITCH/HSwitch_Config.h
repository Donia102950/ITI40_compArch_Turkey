/*
 * HSwitch_Config.h
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */

#ifndef HSWITCH_CONFIG_H_
#define HSWITCH_CONFIG_H_
#include "STD_Types.h"

#define MAX_SWITCH_NUMBER 	 2

typedef struct
 {
	 u8 Switch_Number;
	 u8 Switch_Port;
	 u8 Switch_PinNumber;

 }Switch_t;




#endif /* HSWITCH_CONFIG_H_ */
