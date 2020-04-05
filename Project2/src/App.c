
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
uint_8t TxFrame[2];

uint_8t RxFrame[2];

/*********************************************************************************************************************/


data_frame* TLocal_Buffer=(data_frame*)TxFrame;
data_frame* RLocal_Buffer=(data_frame*)RxFrame;


/*********************************************************************************************************************/

uint_8t DataLengthTX=sizeof(TxFrame);

uint_8t DataLengthRX=sizeof(RxFrame);


/*********************************************************************************************************************/

void AppTask_Runnable (void)
{static uint_8t LocalFlag;

	TLocal_Buffer->SwitchState=HSwitch_GetState(1);			/*switch number macro*/

	if(TLocal_Buffer->SwitchState==PRESSED)
	{
		TLocal_Buffer->LcdCounter++;

		if(TLocal_Buffer->LcdCounter==255)
		{
			TLocal_Buffer->LcdCounter=0;
		}
	}


	/*Receive Data*/

	HUART_ReceiveData(RxFrame,DataLengthRX);


	if(RLocal_Buffer->SwitchState==PRESSED)
	{
		LED_SetLedState(LED_NUMBER,HIGH);
	}
	else
	{
		LED_SetLedState(LED_NUMBER,LOW);
	}

	/*LCD update*/
	LCD_WriteData(&(RLocal_Buffer->LcdCounter),1);

/*Send Data*/
	if(LocalFlag==1)
	{
	HUART_SendData(TLocal_Buffer,DataLengthTX);
	LocalFlag=0;
	}
	else
	{
	LocalFlag=1;
	}
}

