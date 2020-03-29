#include "sched.h"
#include "DRCC.h"
#include "DGPIO.h"
#include "HLCD.h"
#include "HLCD_config.h"


#define FUNCTION_SET						0
#define DISPLAY_ON_OFF						1
#define DISPLAY_CLEAR						2
#define ENTRY_MODE_SET						3

#define IDLE_PROCESS						0
#define WRITE_PROCESS						1
#define CLEAR_PROCESS						2

#define NOT_INITIALIZED 	0
#define INITIALIZED 		1

extern LCDPins_t LCDPins;


task_t LCDTask;
typedef uint_8t CurrentProcess_t;
CurrentProcess_t CurrentProcess=IDLE_PROCESS;
uint_8t InitComplete=NOT_INITIALIZED;
uint_8t Lcd_Data[DATA_BUFFER_SIZE];
uint_8t Lcd_Length;

static void LCD_LCDTask (void);
static void LCD_InitProcess (void);
static void LCD_WriteProcess (void);
static void LCD_ClearProcess (void);

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
			GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
			if(Enable)
			{
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,CLEAR);
				Current_state=DISPLAY_ON_OFF;
			}
			else
			{
				GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,CLEAR);
				GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[0].Port,LCDPins.DataPins[0].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[1].Port,LCDPins.DataPins[1].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[2].Port,LCDPins.DataPins[2].Pin,FONT_SIZE);
				GPIO_Writee(LCDPins.DataPins[3].Port,LCDPins.DataPins[3].Pin,LINES_NUMBER);
				GPIO_Writee(LCDPins.DataPins[4].Port,LCDPins.DataPins[4].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[5].Port,LCDPins.DataPins[5].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[6].Port,LCDPins.DataPins[6].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[7].Port,LCDPins.DataPins[7].Pin,CLEAR);
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);

			}
			break;

		case DISPLAY_ON_OFF:
			GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
			if(Enable)
			{
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,CLEAR);
				Current_state=DISPLAY_CLEAR;
			}
			else
			{
				GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,CLEAR);
				GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[0].Port,LCDPins.DataPins[0].Pin,BLINK_CURSOR);
				GPIO_Writee(LCDPins.DataPins[1].Port,LCDPins.DataPins[1].Pin,DISPLAY_CURSOR);
				GPIO_Writee(LCDPins.DataPins[2].Port,LCDPins.DataPins[2].Pin,DISPLAY_DATA);
				GPIO_Writee(LCDPins.DataPins[3].Port,LCDPins.DataPins[3].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[4].Port,LCDPins.DataPins[4].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[5].Port,LCDPins.DataPins[5].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[6].Port,LCDPins.DataPins[6].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[7].Port,LCDPins.DataPins[7].Pin,CLEAR);
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);

			}
			break;

		case DISPLAY_CLEAR:
			GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
			if(Enable)
			{
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,CLEAR);
				/*Current_state=ENTRY_MODE_SET;*/
				InitComplete=INITIALIZED;
			}
			else
			{
				GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,CLEAR);
				GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[0].Port,LCDPins.DataPins[0].Pin,SET);
				GPIO_Writee(LCDPins.DataPins[1].Port,LCDPins.DataPins[1].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[2].Port,LCDPins.DataPins[2].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[3].Port,LCDPins.DataPins[3].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[4].Port,LCDPins.DataPins[4].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[5].Port,LCDPins.DataPins[5].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[6].Port,LCDPins.DataPins[6].Pin,CLEAR);
				GPIO_Writee(LCDPins.DataPins[7].Port,LCDPins.DataPins[7].Pin,CLEAR);
				GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);

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

static void LCD_WriteProcess (void)
{
	uint_8t Enable;
	uint_8t local_counter;
	uint_8t temp;
	static uint_8t CurrChar;


	GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
	if(Enable)
	{
		GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,CLEAR);
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
			GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,SET);
			GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
			temp=Lcd_Data[CurrChar];
			for(local_counter=0;local_counter<8;local_counter++)
			{
				GPIO_Writee(LCDPins.DataPins[local_counter].Port,LCDPins.DataPins[local_counter].Pin,((temp>>local_counter)&(1)));
			}
			GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);
			CurrChar++;
		}
	}

}

static void LCD_ClearProcess (void)
{
	uint_8t Enable;
	GPIO_ReadPin(LCDPins.EN.Port,LCDPins.EN.Pin,&Enable);
	if(Enable)
	{
		GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,CLEAR);
		CurrentProcess=IDLE_PROCESS;
	}
	else
	{

			GPIO_Writee(LCDPins.RS.Port,LCDPins.RS.Pin,CLEAR);
			GPIO_Writee(LCDPins.RW.Port,LCDPins.RW.Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[0].Port,LCDPins.DataPins[0].Pin,SET);
			GPIO_Writee(LCDPins.DataPins[1].Port,LCDPins.DataPins[1].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[2].Port,LCDPins.DataPins[2].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[3].Port,LCDPins.DataPins[3].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[4].Port,LCDPins.DataPins[4].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[5].Port,LCDPins.DataPins[5].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[6].Port,LCDPins.DataPins[6].Pin,CLEAR);
			GPIO_Writee(LCDPins.DataPins[7].Port,LCDPins.DataPins[7].Pin,CLEAR);
			GPIO_Writee(LCDPins.EN.Port,LCDPins.EN.Pin,SET);
	}
}


uint_8t LCD_Init (void)
{
	uint_8t i,LocalError = OK;
	LCDTask.Runnable=LCD_LCDTask;
	LCDTask.periodicity=2;
	/*First part: configure LCD GPIO Pins*/
	LocalError=GPIO_Config(&(LCDPins.RS));
	if (!LocalError)
		LocalError=GPIO_Config(&(LCDPins.RW));
	if (!LocalError)
		LocalError=GPIO_Config(&(LCDPins.EN));
	if (!LocalError)
	{
		for (i=0;i<8;i++)
		{
			if (!LocalError)
				GPIO_Config(&(LCDPins.DataPins[i]));
		}
	}
	return LocalError;
}

uint_8t LCD_WriteData (const uint_8t *data,uint_8t DataLength)
{
	uint_8t local_counter;
	if(CurrentProcess==IDLE_PROCESS)
	{
		CurrentProcess=WRITE_PROCESS;
		Lcd_Length=DataLength;
		for(local_counter=0;local_counter<Lcd_Length;local_counter++)
		{
			Lcd_Data[local_counter]=data[local_counter];
		}
		return OK;
	}
	else
		return NOT_OK;
}


uint_8t LCD_ClearLCD (void)
{
		if(CurrentProcess==IDLE_PROCESS)
		{
			CurrentProcess=CLEAR_PROCESS;
			return OK;
		}
		else
			return NOT_OK;
}





