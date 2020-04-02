#ifndef SCHED_H
#define SCHED_H

typedef void (* Runnable_t)(void);

typedef struct {
	Runnable_t Runnable;
	uint_32t periodicity;
}task_t;

uint_8t Sched_Init(void);
uint_8t Sched_Start(void);
void Sched_Suspend(void);

#endif
