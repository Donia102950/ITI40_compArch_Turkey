/*
 * HLED_Interface.h
 *
 *
 */

#ifndef HLED_INTERFACE_H_
#define HLED_INTERFACE_H_
#include "GPIO_interface.h"


#define LED_ACTIVE_HIGH 	1
#define LED_ACTIVE_LOW 	    0

typedef struct
{
	GPIO_t* GPIO_cfg;
	uint_8t LED_Number;
	uint_8t LED_MODE; // NEGATIVE OR POSITIVE connection
}LED;

/*********************************************************************************************************************/

void LED_Init(void);
void LED_SetLedState(uint_8t LedNumber , uint_8t state);



#endif /* HLED_INTERFACE_H_ */
