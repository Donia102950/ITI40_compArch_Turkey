/*
 * HLED_Interface.h
 *
 *  Created on: �
 *      Author: alima
 */

#ifndef HLED_INTERFACE_H_
#define HLED_INTERFACE_H_
typedef struct
{
	uint_8t LED_Number;
	uint_8t LED_PIN;
	uint_8t LED_PORT;
	uint_8t LED_MODE; // NEGATIVE OR POSITIVE connection
	uint_8t PIN_MODE;
	uint_8t PIN_SPEED;
}LED;

void LED_Init(void);
void LED_SetLedState(LED * ptr , uint_8t state);



#endif /* HLED_INTERFACE_H_ */
