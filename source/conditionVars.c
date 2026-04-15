#include "conditionVars.h"

void initConditionVar()
{
	cv = malloc(sizeof(conditionVar));
	cv->waiters = 0;

	initBlockMutex();
	semaphore_init();
}

void wait()
{
	__atomic_add_fetch(&(cv->waiters), 1, __ATOMIC_SEQ_CST);
	blockMutex_unlock();
	semaphore_wait();
	blockMutex_lock();
}

void signal()
{
	if (__atomic_load_n(&(cv->waiters), __ATOMIC_SEQ_CST) >= 0)
	{
		semaphore_post();
		cv->waiters--;
	}
}