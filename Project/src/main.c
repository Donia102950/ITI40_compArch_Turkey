
/*********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "Sched.h"
#include "UARTHandler_interface.h"
#include "Hswitch_intertface.h"
#include "HLCD.h"
#include "HLED_Interface.h"
/*********************************************************************************************************************/

task_t task1;
task_t task2;
task_t task3;
task_t task4;
typedef struct{

	uint_8t SwitchState;
	uint_8t LcdCounter;
	uint_8t LedState;
}data_frame;

data_frame TxFrame;
data_frame RxFrame;
/*********************************************************************************************************************/

int main(void)
{
	HSwitch_Init();
	LED_Init();
	 LCD_Init();
	 Sched_Init();
	 Sched_Start();
}

//void task_switch(void){
//	if(switchValue){
//		counter++;
//	}
//	HUART_SendData();
//}


