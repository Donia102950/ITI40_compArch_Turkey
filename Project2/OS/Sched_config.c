#include "STD_TYPES.h"
#include "Sched.h"
#include "Sched_config.h"
#include "HLCD.h"
#include "HLED_Interface.h"
#include "Hswitch_intertface.h"
/*********************************************************************************************************************/


extern task_t LCDTask;
extern task_t SwitchTask;
extern task_t AppTask;

const TaskBaseInfo_t SysTask_info[MAX_TASKS]={
		/*runnable              firstdelay*/
		{.AppTask=&SwitchTask,.FirstDelay=0},
		{.AppTask=&AppTask,.FirstDelay=0},
		{.AppTask=&LCDTask,.FirstDelay=0}

};
/*********************************************************************************************************************/
