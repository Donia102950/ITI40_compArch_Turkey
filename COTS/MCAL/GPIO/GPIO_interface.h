/*define all pins*/
#define PIN0    0x0001
#define PIN1    0x0002
#define PIN2    0x0004
#define PIN3    0x0008
#define PIN4    0x0010
#define PIN5    0x0020
#define PIN6    0x0040
#define PIN7    0x0080
#define PIN8    0x0100
#define PIN9    0x0200
#define PIN10   0x0400
#define PIN11   0x0800
#define PIN12   0x1000
#define PIN13   0x2000
#define PIN14   0x4000
#define PIN15   0x8000

/*define null pointer*/
#define NULL ( (void *) 0)

/*define all modes*/
/*#define MODE_GENERALOUTPUT_PUSHPULL     0b0001
#define MODE_OUTPUT_OPENDRAIN             0b0101
#define MODE_ALTERNATIVROUTPUT_PUSHPULL   0b1001
#define MODE_ALTERNATIVROUTPUT_OPENDRAIN  0b1101
#define MODE_INPUT_ANALOG                 0b0000
#define MODE_INPUT_INPUTFLOATING          0b0100
#define MODE_INPUT_INPUTPULLDOWN          0b1000
#define MODE_INPUT_INPUTPULLUP            0b1010   //to change the pulldown and pullup and i will handle it in function to return it check it*/

/*define all modes*/
typedef enum 
{
	MODE_INPUT_ANALOG = 0b0000,
	MODE_INPUT_INPUTFLOATING =0b0001,
	MODE_INPUT_INPUTPULLDOWN =0b0010,
	MODE_INPUT_INPUTPULLUP=0b0110,
	MODE_OUTPUT_OPENDRAIN=0b1101,
	MODE_GENERALOUTPUT_PUSHPULL=0b1110,     //0x10
	MODE_ALTERNATIVROUTPUT_PUSHPULL=0b1110,
    MODE_ALTERNATIVROUTPUT_OPENDRAIN=0b1111,

}Mode;
 

/*define speed */
/*#define INPUT           0b00
#define SPEED_10MHZ     0b01
#define SPEED_2MHZ      0b10
#define SPEED_50MHZ     0b11 */

#define ON 0
#define OFF 1
#define maxpin 15
#define minpin 0
#define MODENUM 4

typedef enum
{
	SPEED_10MHZ=0b0111,
	SPEED_2MHZ=0b1011,
	SPEED_50MHZ=0b1111,
}Speed;

//#define SPEED_10MHZ 1

/*define ports*/
#define PORTA  0
#define PORTB  1
#define PORTC  2

/*all the configurations to input and output pins (4pins) in struct*/
typedef struct
{
	 u16      pin;
	 Mode     mode;
	 Speed    speed;
	 u8        port;
}GPIO_t;


/*function of the configuration */
void GPIO_u8SetConfiguration(GPIO_t *p);
void GPIO_u8SetValue(GPIO_t *p,u8 state);
void GPIO_u8getValue(GPIO_t *p,u8 *state);
