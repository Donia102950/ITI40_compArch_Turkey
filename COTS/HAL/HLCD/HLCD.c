/*******************************************************************************************************************************************************/
/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.2*/
/*NAME: HLCD_DRIVER */
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*includes*/
#include "STD_TYPES2.h"
#include "sched.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "HLCD_config.h"
#include "HLCD.h"
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/*general definitions*/
/*the functions of LCD in the intialization*/
#define FUNCTION_SET						0
#define DISPLAY_ON_OFF						1
#define DISPLAY_CLEAR						2
#define ENTRY_MODE_SET						3

/*all commands*/
#define IDLE_PROCESS						0
#define WRITE_PROCESS						1
#define CLEAR_PROCESS						2

#define NOT_INITIALIZED 	0
#define INITIALIZED 		1
typedef uint_8t CurrentProcess_t;
/********************************************************************************************************************************************************/

/********************************************************************************************************************************************************/
/*Globals variables*/
extern LCDPins_t LCDPins;
task_t LCDTask;
CurrentProcess_t CurrentProcess=IDLE_PROCESS;
static uint_8t InitComplete=NOT_INITIALIZED;
static uint_8t Lcd_Data[DATA_BUFFER_SIZE];
static uint_8t Lcd_Length;
/********************************************************************************************************************************************************/

/********************************************************************************************************************************************************/
/*prototypes of all commands */
static void LCD_LCDTask (void);
static void LCD_InitProcess (void);
static void LCD_WriteProcess (void);
static void LCD_ClearProcess (void);
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : to set the LCD tasks
 * Inputs:void
 * Output: void                         */
/********************************************************************************************************************************************************/
static void LCD_LCDTask (void)
{
	if(InitComplete)
	{
		switch(CurrentProcess)
		{
		case IDLE_PROCESS:
			break;
		case WRITE_PROCESS:
			LCD_WriteProcess();
			break;
		case CLEAR_PROCESS:
			LCD_ClearProcess();
			break;
		}
	}
	else
	{
		LCD_InitProcess();
	}
}
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : to init the process
 * Inputs:void
 * Output: void                         */
/********************************************************************************************************************************************************/
static void LCD_InitProcess (void)
{
	static uint_8t Current_state=FUNCTION_SET;
	static uint_8t counter;
	uint_8t Enable;

	counter++;

	if(counter>=15)
	{
		switch(Current_state)
		{
		case FUNCTION_SET:
			GPIO_u8getValue(&(LCDPins.EN),LCDPins.EN.pin,&Enable);
			if(Enable)
			{
				GPIO_u8SetValue(&LCDPins.EN,LCDPins.EN.pin,CLEAR);
				Current_state=DISPLAY_ON_OFF;
			}
			else
			{
				GPIO_u8SetValue(&LCDPins.RS,LCDPins.RS.pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.RW,LCDPins.RW.pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.DataPins[0],LCDPins.DataPins[0].pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.DataPins[1],LCDPins.DataPins[1].pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.DataPins[2],LCDPins.DataPins[2].pin,FONT_SIZE);
				GPIO_u8SetValue(&LCDPins.DataPins[3],LCDPins.DataPins[3].pin,LINES_NUMBER);
				GPIO_u8SetValue(&LCDPins.DataPins[4],LCDPins.DataPins[4].pin,SET);
				GPIO_u8SetValue(&LCDPins.DataPins[5],LCDPins.DataPins[5].pin,SET);
				GPIO_u8SetValue(&LCDPins.DataPins[6],LCDPins.DataPins[6].pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.DataPins[7],LCDPins.DataPins[7].pin,CLEAR);
				GPIO_u8SetValue(&LCDPins.EN,LCDPins.EN.pin,SET);

			}
			break;

		case DISPLAY_ON_OFF:
			GPIO_u8getValue(&(LCDPins.EN),LCDPins.EN.pin,&Enable);
			if(Enable)
			{
				GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,CLEAR);
				Current_state=DISPLAY_CLEAR;
			}
			else
			{
				GPIO_u8SetValue(&(LCDPins.RS),LCDPins.RS.pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.RW),LCDPins.RW.pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[0]),LCDPins.DataPins[0].pin,BLINK_CURSOR);
				GPIO_u8SetValue(&(LCDPins.DataPins[1]),LCDPins.DataPins[1].pin,DISPLAY_CURSOR);
				GPIO_u8SetValue(&(LCDPins.DataPins[2]),LCDPins.DataPins[2].pin,DISPLAY_DATA);
				GPIO_u8SetValue(&(LCDPins.DataPins[3]),LCDPins.DataPins[3].pin,SET);
				GPIO_u8SetValue(&(LCDPins.DataPins[4]),LCDPins.DataPins[4].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[5]),LCDPins.DataPins[5].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[6]),LCDPins.DataPins[6].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[7]),LCDPins.DataPins[7].pin,CLEAR);

				GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,SET);

			}
			break;

		case DISPLAY_CLEAR:
			GPIO_u8getValue(&(LCDPins.EN),LCDPins.EN.pin,&Enable);
			if(Enable)
			{
				GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,CLEAR);
				/*Current_state=ENTRY_MODE_SET;*/
				InitComplete=INITIALIZED;
			}
			else
			{
				GPIO_u8SetValue(&(LCDPins.RS),LCDPins.RS.pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.RW),LCDPins.RW.pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[0]),LCDPins.DataPins[0].pin,SET);
				GPIO_u8SetValue(&(LCDPins.DataPins[1]),LCDPins.DataPins[1].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[2]),LCDPins.DataPins[2].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[3]),LCDPins.DataPins[3].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[4]),LCDPins.DataPins[4].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[5]),LCDPins.DataPins[5].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[6]),LCDPins.DataPins[6].pin,CLEAR);
				GPIO_u8SetValue(&(LCDPins.DataPins[7]),LCDPins.DataPins[7].pin,CLEAR);

				GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,SET);

			}
			break;

			/*case ENTRY_MODE_SET:
			GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
			if(Enable)
			{
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);
				Current_state=ENTRY_MODE_SET;
			}
			else
			{
				GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,CLEAR);
				GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[0].Port,LCDPins.DataPins[0].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[1].Port,LCDPins.DataPins[1].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[2].Port,LCDPins.DataPins[2].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[3].Port,LCDPins.DataPins[3].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[4].Port,LCDPins.DataPins[4].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[5].Port,LCDPins.DataPins[5].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[6].Port,LCDPins.DataPins[6].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[7].Port,LCDPins.DataPins[7].Pin,CLEAR);
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);

			}
			break;*/

		}
	}
	else
	{
		asm("NOP");
	}

}
/********************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
/* Dsecription : to write on the lcd
 * Inputs:void
 * Output: void                         */
/********************************************************************************************************************************************************/
static void LCD_WriteProcess (void)
{
	uint_8t Enable;
	uint_8t local_counter;
	uint_8t temp;
	static uint_8t CurrChar;

	GPIO_u8getValue(&(LCDPins.EN),LCDPins.EN.pin,&Enable);
	if(Enable)
	{
		GPIO_u8SetValue(&LCDPins.EN,LCDPins.EN.pin,CLEAR);
	}
	else
	{
		if (Lcd_Length==CurrChar)
		{
			CurrentProcess=IDLE_PROCESS;
			CurrChar=0;
		}
		else
		{
			GPIO_u8SetValue(&(LCDPins.RS),LCDPins.RS.pin,SET);
			GPIO_u8SetValue(&(LCDPins.RW),LCDPins.RW.pin,CLEAR);
			temp=Lcd_Data[CurrChar];
			for(local_counter=0;local_counter<8;local_counter++)
			{
				GPIO_u8SetValue(&(LCDPins.DataPins[local_counter]),LCDPins.DataPins[local_counter].pin,((temp>>local_counter)&(1)));
			}
			GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,SET);
			CurrChar++;
		}
	}

}
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : to clear the lcd
 * Inputs:void
 * Output: void                         */
/********************************************************************************************************************************************************/
static void LCD_ClearProcess (void)
{
	uint_8t Enable;
	GPIO_u8getValue(&(LCDPins.EN),LCDPins.EN.pin,&Enable);
	if(Enable)
	{
		GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,CLEAR);
		CurrentProcess=IDLE_PROCESS;
	}
	else
	{

		GPIO_u8SetValue(&(LCDPins.RS),LCDPins.RS.pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.RW),LCDPins.RW.pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[0]),LCDPins.DataPins[0].pin,SET);
		GPIO_u8SetValue(&(LCDPins.DataPins[1]),LCDPins.DataPins[1].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[2]),LCDPins.DataPins[2].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[3]),LCDPins.DataPins[3].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[4]),LCDPins.DataPins[4].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[5]),LCDPins.DataPins[5].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[6]),LCDPins.DataPins[6].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.DataPins[7]),LCDPins.DataPins[7].pin,CLEAR);
		GPIO_u8SetValue(&(LCDPins.EN),LCDPins.EN.pin,SET);
	}
}
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : the init of LCD to configure the pins
 * Inputs:void
 * Output: standard error                         */
/********************************************************************************************************************************************************/
uint_8t LCD_Init (void)
{
	uint_8t i;
	uint_8t local_Error=OK;
	LCDTask.Runnable=LCD_LCDTask;
	LCDTask.periodicity=2;
	/*First part: configure LCD GPIO Pins*/
	local_Error=GPIO_u8SetConfiguration(&(LCDPins.RS));
	local_Error|=GPIO_u8SetConfiguration(&(LCDPins.RW));
	local_Error|=GPIO_u8SetConfiguration(&(LCDPins.EN));


	for (i=0;i<8;i++)
	{

			GPIO_u8SetConfiguration(&(LCDPins.DataPins[i]));
	}

	return local_Error;
}
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : the init of write data
 * Inputs:void
 * Output: standard error                         */
/********************************************************************************************************************************************************/
uint_8t LCD_WriteData (const uint_8t *data,uint_8t DataLength)
{
	uint_8t local_counter , local_Error=OK;
	if(CurrentProcess==IDLE_PROCESS)
	{
		CurrentProcess=WRITE_PROCESS;
		Lcd_Length=DataLength;
		for(local_counter=0;local_counter<Lcd_Length;local_counter++)
		{
			Lcd_Data[local_counter]=data[local_counter];
		}
	}
	else
		local_Error=NOT_OK;

	return local_Error;
}
/********************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
/* Dsecription : the init of clear data
 * Inputs:void
 * Output: standard error                         */
/********************************************************************************************************************************************************/
uint_8t LCD_ClearLCD (void)
{
	uint_8t local_Error=OK;
	if(CurrentProcess==IDLE_PROCESS)
	{
		CurrentProcess=CLEAR_PROCESS;
	}
	else
		local_Error=NOT_OK;

	return local_Error;
}
/********************************************************************************************************************************************************/




