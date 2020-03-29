/*
 * Hswitch_intertface.h
 *
 *  Created on: Mar 22, 2020
 *      Author: mina Yousry
 */

#ifndef HSWITCH_INTERTFACE_H_
#define HSWITCH_INTERTFACE_H_
#include "STD_Types.h"




#define GPIO_PIN_NUM0	0
#define GPIO_PIN_NUM1	1
#define GPIO_PIN_NUM2	2
#define GPIO_PIN_NUM3	3
#define GPIO_PIN_NUM4	4
#define GPIO_PIN_NUM5	5
#define GPIO_PIN_NUM6	6
#define GPIO_PIN_NUM7	7
#define GPIO_PIN_NUM8	8
#define GPIO_PIN_NUM9	9
#define GPIO_PIN_NUM10	10
#define GPIO_PIN_NUM11	11
#define GPIO_PIN_NUM12	12
#define GPIO_PIN_NUM13	13

#define GPIO_PORTA	'A'
#define GPIO_PORTB	'B'
#define GPIO_PORTC	'C'



extern u8 HSwitch_GetState(u8 Switch_num);

#endif /* HSWITCH_INTERTFACE_H_ */
