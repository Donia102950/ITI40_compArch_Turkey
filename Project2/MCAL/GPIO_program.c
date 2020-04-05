/*******************************************************************************************************************************************************/
/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.2*/
/*NAME: GPIO DRIVER */
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*includes*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
/*******************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/*structure which contains all the registers of GPIO*/
typedef struct{
	uint_32t CRL;
	uint_32t CRH;
	uint_32t IDR;
	uint_32t ODR;
	uint_32t BSRR;
	uint_32t BRR;
	uint_32t LCKR;
}Reg;
/********************************************************************************************************************************************************/

/********************************************************************************************************************************************************/
/*pointer to each port*/
#define PORTA_POINTER  ((volatile Reg *)(0x40010800))
#define PORTB_POINTER  ((volatile Reg *)(0x40010C00))
#define PORTC_POINTER  ((volatile Reg *)(0x40011000))
/********************************************************************************************************************************************************/

/********************************************************************************************************************************************************/
/*general defines*/
#define maxpin 15             /*maximum number of pins        */
#define minpin 0             /*minimum number of pins        */
#define MODENUM 4           /*number of shifting of any mode*/
#define Mode_null 0b1100   /*to set the correct mode       */
#define speed_null 0b0011 /*to set the correct speed      */
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : to set the configuration to each pin
 * Inputs: pointer to structure of GPIO
 * Output: standard error                          */
/*******************************************************************************************************************************************************/
uint_8t GPIO_u8SetConfiguration(GPIO_t *p)
{
	uint_8t Mode ,mode,speed,j=0,i;
	uint_8t local_Error=OK;

	if( p->port == PORTA || p->port == PORTB || p->port == PORTC)
	{
		switch(p->port)
		{
		case PORTA:
			for (i=minpin;i<=maxpin;i++)
			{
				if((((p->pin)>>i)&0x01)==1)
				{

					mode=p->mode&(Mode_null);
					speed=p->speed&(speed_null);
					Mode= (mode)|(speed);
					if(i<=7)
					{
						PORTA_POINTER->CRL&=~(0b1111<<i*MODENUM);
						PORTA_POINTER->CRL|=(Mode<<i*MODENUM);
					}
					else if(i>7 && i<16)
					{
						j=i-8;
						PORTA_POINTER->CRH&=~(0b1111<<j*MODENUM);
						PORTA_POINTER->CRH|=(Mode<<j*MODENUM);
					}

					if(p->mode == MODE_INPUT_INPUTPULLDOWN)
					{
						PORTA_POINTER->ODR &=(uint_32t) ~(1<<i);
					}
					else if(p->mode == MODE_INPUT_INPUTPULLUP)
					{
						PORTA_POINTER->ODR |=(uint_32t) (1<<i);
					}
				}
			}
			break;
		case PORTB:
			for (i=minpin;i<maxpin;i++)
			{
				if(((p->pin>>i)&0x01)==1)
				{

					mode=p->mode&(Mode_null);
					speed=p->speed&(speed_null);
					Mode= (mode)|(speed);

					if(i<=7)
					{
						PORTB_POINTER->CRL&=~(0b1111<<i*MODENUM);
						PORTB_POINTER->CRL|=(Mode<<i*MODENUM);
					}
					else if(i>7)
					{
						j=i-8;
						PORTB_POINTER->CRH&=~(0b1111<<j*MODENUM);
						PORTB_POINTER->CRH|=(Mode<<j*MODENUM);
					}

					if(p->mode == MODE_INPUT_INPUTPULLDOWN)
					{
						PORTB_POINTER->ODR &=(uint_32t) ~(1<<i);
					}
					else if(p->mode == MODE_INPUT_INPUTPULLUP)
					{
						PORTB_POINTER->ODR |=(uint_32t) (1<<i);
					}
				}
			}
			break;
		case PORTC:
			for (i=minpin;i<maxpin;i++)
			{


				if(((p->pin>>i)&0x01)==1)
				{

					mode=p->mode&(Mode_null);
					speed=p->speed&(speed_null);
					Mode= (mode)|(speed);
					//Mode=0b0010;
					if(i<=7)
					{
						PORTC_POINTER->CRL&=~(0b1111<<i*MODENUM);
						PORTC_POINTER->CRL|=(Mode<<i*MODENUM);
					}
					else if(i>7)
					{
						j=i-8;
						//Mode=0b0010;
						PORTC_POINTER->CRH&=~(0b1111<<j*MODENUM);
						PORTC_POINTER->CRH|=(Mode<<j*MODENUM);
					}

					if(p->mode == MODE_INPUT_INPUTPULLDOWN)
					{
						PORTC_POINTER->ODR &=(uint_32t) ~(1<<i);
					}
					else if(p->mode == MODE_INPUT_INPUTPULLUP)
					{
						PORTC_POINTER->ODR |=(uint_32t) (1<<i);
					}
				}
			}
			break;

		}
	}else
	{
		local_Error=NOK;
	}
	return local_Error;

}



/********************************************************************************************************************************************************/
/* Dsecription : to set the value of whole struct
 * Inputs: pointer to structure of GPIO , state
 * Output: standard error                          */
/********************************************************************************************************************************************************/

uint_8t GPIO_u8SetValue(GPIO_t *p,uint_32t pin,uint_8t state)
{
	uint_8t local_Error=OK;
	switch(p->port)
	{
	case PORTA:
		if(state==SET)
		{
			PORTA_POINTER->BSRR=pin;
		}else if (state==CLEAR)
		{
			PORTA_POINTER->BRR=pin;
		}
		break;
	case PORTB:
		if(state==SET)
		{
			PORTB_POINTER->BSRR=pin;
		}else if (state==CLEAR)
		{
			PORTB_POINTER->BRR=pin;
		}
		break;
	case PORTC:
		if(state==SET)
		{
			//PORTC_POINTER->ODR|=(p->pin);
			PORTC_POINTER->BSRR=pin;
		}else if (state==CLEAR)
		{
			//PORTC_POINTER->ODR&=~(p->pin);
			PORTC_POINTER->BRR=pin;
		}break;
	default:
		local_Error=NOK;
		break;

	}
	return local_Error;
}



/*******************************************************************************************************************************************************/
/* Dsecription : to get the value of whole object
 * Inputs: pointer to structure of GPIO , pointer to state
 * Output: standard error                          */
/*******************************************************************************************************************************************************/

uint_8t GPIO_u8getValue(GPIO_t *p,uint_32t pin ,uint_8t *state)
{
	uint_8t local_Error=OK;
	switch(p->port)
	{
	case PORTA:
		if( ((PORTA_POINTER->IDR) & ( pin ) ) )
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=1;/**           1 -------------- pressed  */
			else *state=0;
		}
		else
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=0;/**           0 -------------- released  */
			else *state=1;
		}
		break;
	case PORTB:
		if( (PORTB_POINTER->IDR) & (pin))
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=1;/**           1 -------------- pressed  */
			else *state=0 ;
		}
		else
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=0;/**           0 -------------- released  */
			else *state=1;
		}
		break;
	case PORTC:
		if( (PORTC_POINTER->IDR) & (pin) )
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=1;/**           1 -------------- pressed  */
			else *state=0 ;
		}
		else
		{
			if(p->mode==MODE_INPUT_INPUTPULLDOWN)*state=0;/**           0 -------------- released  */
			else *state=1;
		}
		break;
	default :
		local_Error=NOK;
		break;
	}
	return local_Error;
}

