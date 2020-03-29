#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

/*structure which contains all the registers*/
typedef struct{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
}Register;


/*set offset values
#define PORTA_BASE_ADDRESS  (u32) 0x40010800
#define PORTB_BASE_ADDRESS  (u32) 0x40010C00
#define PORTC_BASE_ADDRESS  (u32) 0x40011000
#define PORTA_OFFSET      *((volatile u32*)(0x40010800))
#define PORTB_OFFSET      *((volatile u32*)(0x40010C00))
#define PORTC_OFFSET      *((volatile u32*)(0x40011000))*/

/*pointer to structure*/
#define PORTA_POINTER  ((Register *)(0x40010800))
#define PORTB_POINTER  ((Register *)(0x40010C00))
#define PORTC_POINTER  ((Register *)(0x40011000))
#define speed_null 0b0011

/*function of the configuration */
void GPIO_u8SetConfiguration(GPIO_t *p)
{
	u8 Mode,j=0,i;
	switch(p->port)
	{
	case PORTA:
		for (i=minpin;i<=maxpin;i++)
		{
			if(((p->pin>>i)&0x01)==1)
			{

				p->mode&=(speed_null);
				Mode= (p->mode)|(p->speed);
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
			}
		}
		break;
	case PORTB:
		for (i=minpin;i<maxpin;i++)
		{
			if(((p->pin>>i)&0x01)==1)
			{

				p->mode&=(speed_null);
				Mode= (p->mode)|(p->speed);

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
			}
		}
		break;
	case PORTC:
		for (i=minpin;i<maxpin;i++)
		{


			if(((p->pin>>i)&0x01)==1)
			{

				p->mode&=speed_null;
				Mode= (p->mode)|(p->speed);
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
			}
		}
		break;

	}

}


void GPIO_u8SetValue(GPIO_t *p,u8 state)
{
	switch(p->port)
	{
	case PORTA:
		if(state==ON)
		{
			PORTA_POINTER->BSRR=p->pin;
		}else
		{
			PORTA_POINTER->BRR=p->pin;
		}
		break;
	case PORTB:
		if(state==ON)
		{
			PORTB_POINTER->BSRR=p->pin;
		}else
		{
			PORTB_POINTER->BRR=p->pin;
		}
		break;
	case PORTC:
		if(state==ON)
		{
			//PORTC_POINTER->ODR|=(p->pin);
			PORTC_POINTER->BRR=p->pin;
		}else
		{
			//PORTC_POINTER->ODR&=~(p->pin);
			PORTC_POINTER->BSRR=p->pin;
		}break;

	}
}



void GPIO_u8getValue(GPIO_t *p,u8 *state)
{
	switch(p->port)
	{
	case PORTA:
		if(PORTA_POINTER->BRR&p->pin ==1)
		{
			state=1;
		}
		else
		{
			state=0;
		}
		break;
	case PORTB:
		if(PORTB_POINTER->BRR&p->pin ==1)
		{
			state=1;
		}
		else
		{
			state=0;
		}
		break;
	case PORTC:
		if(PORTC_POINTER->BRR&p->pin ==1)
		{
			state=1;
		}
		else
		{
			state=0;
		}
		break;

	}
}

