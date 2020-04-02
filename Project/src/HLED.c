#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "HLED_private.h"
#include "HLED_config.h"
#include "HLED_Interface.h"


GPIO_t Gpio[LEDS_NUMBER];
LED Led[LEDS_NUMBER];
LED * ptr1 = Led;
GPIO_t * ptr2 = Gpio;


void LED_Init(void)
{
	for(int i=0;i<LEDS_NUMBER;i++)
	{
		ptr2[i].pin = ptr1[i].LED_PIN;
		ptr2[i].mode = ptr1[i].PIN_MODE;
		ptr2[i].port = ptr1[i].LED_PORT;
		ptr2[i].speed = ptr1[i].PIN_SPEED;
		GPIO_u8SetConfiguration(ptr2);
	}
}

void LED_SetLedState(LED * ptr , uint_8t state)
{
	if( ptr->LED_MODE == LED_ACTIVE_HIGH)
		{

			if(state == ON)
		{
			GPIO_u8SetValue(ptr2,ptr->LED_PIN,state);
		}
		else if(state == OFF)
		{
			GPIO_u8SetValue(ptr2,ptr->LED_PIN,~state);
		}

	}
	else if( ptr->LED_MODE == LED_ACTIVE_LOW)
	{

		if(state == ON)
		{
			GPIO_u8SetValue(ptr2,ptr->LED_PIN,~state);
		}
		else if(state == OFF)
		{
			GPIO_u8SetValue(ptr2,ptr->LED_PIN,state);
		}

	}
}
