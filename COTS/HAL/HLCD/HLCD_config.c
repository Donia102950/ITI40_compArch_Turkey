/*******************************************************************************************************************************************************/
/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.2*/
/*NAME: HLCD DRIVER */
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*includes*/
#include "GPIO_interface.h"

#include "HLCD_config.h"
/*******************************************************************************************************************************************************/

/******************************************************************************************************************************************************/
/*to configure all the pins of LCD*/
 const LCDPins_t LCDPins= {
.RS.port= PORTA,.RS.pin=PIN9,.RS.mode=MODE_GENERALOUTPUT_PUSHPULL,.RS.speed=SPEED_2MHZ,
.RW.port= PORTA,.RW.pin=PIN10,.RW.mode=MODE_GENERALOUTPUT_PUSHPULL,.RW.speed=SPEED_2MHZ,
.EN.port= PORTA,.EN.pin=PIN11,.EN.mode=MODE_GENERALOUTPUT_PUSHPULL,.EN.speed=SPEED_2MHZ,
.DataPins[0].port= PORTA,.DataPins[0].pin=PIN0,.DataPins[0].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[0].speed=SPEED_2MHZ,
.DataPins[1].port= PORTA,.DataPins[1].pin=PIN1,.DataPins[1].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[1].speed=SPEED_2MHZ,
.DataPins[2].port= PORTA,.DataPins[2].pin=PIN2,.DataPins[2].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[2].speed=SPEED_2MHZ,
.DataPins[3].port= PORTA,.DataPins[3].pin=PIN3,.DataPins[3].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[3].speed=SPEED_2MHZ,
.DataPins[4].port= PORTA,.DataPins[4].pin=PIN4,.DataPins[4].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[4].speed=SPEED_2MHZ,
.DataPins[5].port= PORTA,.DataPins[5].pin=PIN5,.DataPins[5].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[5].speed=SPEED_2MHZ,
.DataPins[6].port= PORTA,.DataPins[6].pin=PIN6,.DataPins[6].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[6].speed=SPEED_2MHZ,
.DataPins[7].port= PORTA,.DataPins[7].pin=PIN7,.DataPins[7].mode=MODE_GENERALOUTPUT_PUSHPULL,.DataPins[7].speed=SPEED_2MHZ
};
/********************************************************************************************************************************************************/
