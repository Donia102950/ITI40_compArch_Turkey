#include "Sched.h"
#ifndef SCHED_CONFIG_H
#define SCHED_CONFIG_H

#define SCHED_TICK_mSEC 5
#define MAX_TASKS 3
/*********************************************************************************************************************/

typedef struct
{
	task_t * AppTask;
	uint_32t FirstDelay;
}TaskBaseInfo_t;


#endif
