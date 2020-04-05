
/*********************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "HLED_private.h"
#include "HLED_config.h"
#include "HLED_Interface.h"
#include "GPIO_interface.h"

/*********************************************************************************************************************/

extern LED Led[LEDS_NUMBER];

void LED_Init(void)
{
	for(int i=0;i<LEDS_NUMBER;i++)
	{

		GPIO_u8SetConfiguration((Led[i].GPIO_cfg));
	}
}
/*********************************************************************************************************************/

void LED_SetLedState(uint_8t LedNumber , uint_8t state)
{

	if( Led[LedNumber].LED_MODE==LED_ACTIVE_HIGH)
		{

			if(state == ON)
		{
			GPIO_u8SetValue((Led[LedNumber].GPIO_cfg),Led[LedNumber].GPIO_cfg->pin,state);
		}
		else if(state == OFF)
		{
			GPIO_u8SetValue((Led[LedNumber].GPIO_cfg),Led[LedNumber].GPIO_cfg->pin,state);
		}

	}
	else if( Led[LedNumber].LED_MODE==LED_ACTIVE_LOW)
	{
		if( Led[LedNumber].LED_MODE==LED_ACTIVE_HIGH)
				{

					if(state == ON)
				{
					GPIO_u8SetValue((Led[LedNumber].GPIO_cfg),Led[LedNumber].GPIO_cfg->pin,~state);
				}

				}

				else if(state == OFF)
				{
					GPIO_u8SetValue((Led[LedNumber].GPIO_cfg),(Led[LedNumber].GPIO_cfg->pin),~state);
				}

			}

}
