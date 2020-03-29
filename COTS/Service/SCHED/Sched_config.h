
#ifndef SCHED_CONFIG_H_
#define SCHED_CONFIG_H_
#define SCHED_TICK_mSEC 100
#define MAX_TASKS 2
typedef struct
{
	task_t * AppTask;
	uint_32t FirstDelay;
}TaskBaseInfo_t;


#endif /* SCHED_CONFIG_H_ */
