
/*********************************************************************************************************************/
/*
 * Author : Mina ,Menna ,Donia ,Hamam ,Nouran
 *
 * Date : 4/2/2020
 *
 * Version : V01
 *
 */
/*********************************************************************************************************************/

#include "STD_TYPES.h"
#include "Sched.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "UARTHandler_interface.h"
#include "Hswitch_intertface.h"
#include "HLCD.h"
#include "HLED_Interface.h"
/*********************************************************************************************************************/
#define PRESSED 		1
#define RELEASED 		0
#define HIGH 			1
#define LOW 			0

#define QUEUE_LENGTH	1

#define LED_NUMBER 		1
/*********************************************************************************************************************/
void AppTask_Runnable (void);
/*********************************************************************************************************************/

task_t AppTask={.Runnable=AppTask_Runnable,.periodicity=100};
/*********************************************************************************************************************/

typedef struct{

	uint_8t SwitchState;
	uint_8t LcdCounter;
}data_frame;
/*********************************************************************************************************************/

static int_8t Queue_Counter=0;
/*********************************************************************************************************************/
data_frame TxFrame[QUEUE_LENGTH];

data_frame RxFrame[QUEUE_LENGTH];

/*********************************************************************************************************************/

uint_8t* RLocal_Buffer=RxFrame;
uint_8t* TLocal_Buffer=TxFrame;

/*********************************************************************************************************************/

uint_8t DataLengthTX=sizeof(TxFrame);

uint_8t DataLengthRX=sizeof(RxFrame);


/*********************************************************************************************************************/

void AppTask_Runnable (void)
{

	TxFrame[Queue_Counter].SwitchState=HSwitch_GetState(1);			/*switch number macro*/
	if(TxFrame[Queue_Counter].SwitchState==PRESSED)
	{
		TxFrame[Queue_Counter].LcdCounter++;

		if(TxFrame[Queue_Counter].LcdCounter==255)
		{
			TxFrame[Queue_Counter].LcdCounter=0;
		}
	}


/*For Loop for Queue*/

	HUART_ReceiveData(RLocal_Buffer,DataLengthRX);

	RxFrame[Queue_Counter].SwitchState=*(RLocal_Buffer);

	RxFrame[Queue_Counter].LcdCounter=*(RLocal_Buffer+1);


	if(RxFrame[Queue_Counter].SwitchState==PRESSED)
	{
		LED_SetLedState(LED_NUMBER,HIGH);
	}
	else
	{
		LED_SetLedState(LED_NUMBER,LOW);
	}


	/*LCD update*/



	LCD_WriteData(&(RxFrame[Queue_Counter].LcdCounter),1);



	/*For loop For Queue*/
	*TLocal_Buffer=TxFrame[Queue_Counter].SwitchState;

	*(TLocal_Buffer+1)=TxFrame[Queue_Counter].LcdCounter;


	HUART_SendData(TLocal_Buffer,DataLengthTX);




}

