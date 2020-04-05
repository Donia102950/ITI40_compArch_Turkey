#include "HLED_Interface.h"
#include "HLED_config.h"



#define LED_ACTIVE_HIGH 	1
#define LED_ACTIVE_LOW 	    0


GPIO_t LedCfg={.pin=PIN13,.mode=MODE_ALTERNATIVROUTPUT_PUSHPULL,.speed=SPEED_50MHZ,.port=PORTC};
LED Led[LEDS_NUMBER]={{.GPIO_cfg=&(LedCfg),.LED_MODE=LED_ACTIVE_LOW,.LED_Number=1}};









