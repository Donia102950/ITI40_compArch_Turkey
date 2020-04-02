/*******************************************************************************************************************************************************/
/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.2*/
/*NAME: GPIO DRIVER */
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
#include "STD_TYPES.h"
/*define all pins*/
#define PIN0    0x00000001
#define PIN1    0x00000002
#define PIN2    0x00000004
#define PIN3    0x00000008
#define PIN4    0x00000010
#define PIN5    0x00000020
#define PIN6    0x00000040
#define PIN7    0x00000080
#define PIN8    0x00000100
#define PIN9    0x00000200
#define PIN10   0x00000400
#define PIN11   0x00000800
#define PIN12   0x00001000
#define PIN13   0x00002000
#define PIN14   0x00004000
#define PIN15   0x00008000
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*define all modes*/
typedef enum
{
	MODE_INPUT_ANALOG = 0b0000,
	MODE_INPUT_INPUTFLOATING =0b0100,
	MODE_INPUT_INPUTPULLDOWN =0b1000,
	MODE_INPUT_INPUTPULLUP=0b1010,
	MODE_OUTPUT_OPENDRAIN=0b0111,
	MODE_GENERALOUTPUT_PUSHPULL=0b0011,
	MODE_ALTERNATIVROUTPUT_PUSHPULL=0b1011,
    MODE_ALTERNATIVROUTPUT_OPENDRAIN=0b1111,

}Mode;
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/* define all the speed*/
typedef enum
{
	SPEED_INPUT=0b0000,
	SPEED_10MHZ=0b1101,
	SPEED_2MHZ=0b1110,
	SPEED_50MHZ=0b1111,
}Speed;
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*define ports*/
#define PORTA  0
#define PORTB  1
#define PORTC  2
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*to define the values in any pins*/
#define SET   1
#define CLEAR 0
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*structure which contains all the configuration of any pin
 * pin   : from PIN0 to PIN15
 * mode  : can be MODE_INPUT_ANALOG / MODE_INPUT_INPUTFLOATING / MODE_INPUT_INPUTPULLDOWN / MODE_INPUT_INPUTPULLUP / MODE_OUTPUT_OPENDRAIN / MODE_GENERALOUTPUT_PUSHPULL/ MODE_ALTERNATIVROUTPUT_OPENDRAIN
 * speed : SPEED_10MHZ / SPEED_2MHZ / SPEED_50MHZ
 * Port  : PORTA / PORTB / PORTC*/
typedef struct
{
	 uint_32t      pin;
	 Mode          mode;
	 Speed         speed;
	 uint_8t       port;
}GPIO_t;
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
 /* Dsecription : to set the configuration to each pin
 * Inputs: pointer to structure of GPIO
 * Output: standard error                          */
/*******************************************************************************************************************************************************/
uint_8t GPIO_u8SetConfiguration(GPIO_t *p);


/*******************************************************************************************************************************************************/
 /* Dsecription : to set the value of any pin
 * Inputs: pointer to structure of GPIO , state (on , off)
 * Output: standard error                          */
/*******************************************************************************************************************************************************/
uint_8t GPIO_u8SetValue(GPIO_t *p,uint_32t pin,uint_8t state);

/*******************************************************************************************************************************************************/
 /* Dsecription : to get the value of any pin
 * Inputs: pointer to structure of GPIO , pointer to state
 * Output: standard error                          */
/*******************************************************************************************************************************************************/
uint_8t GPIO_u8getValue(GPIO_t *p, uint_32t pin ,uint_8t *state);

#endif
