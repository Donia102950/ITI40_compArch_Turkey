#include "STD_TYPES.h"
#include "Sched.h"
#include "Sched_config.h"
/*********************************************************************************************************************/

extern task_t task1;
extern task_t task2;
const TaskBaseInfo_t SysTask_info[MAX_TASKS]={
		{.AppTask=&task1,.FirstDelay=500},
		{.AppTask=&task2,.FirstDelay=0}
};
/*********************************************************************************************************************/
