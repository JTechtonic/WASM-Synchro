#include "conditionVars.h"
/***
 * Now look into implementing semaphores
 * https://www.geeksforgeeks.org/operating-systems/semaphores-in-process-synchronization/
 * https://gist.github.com/mepcotterell/6f0a779befe388ab822764255e3776ae
 * https://www.google.com/search?client=firefox-b-1-d&q=implementing+semaphores
 * 
 */


void initConditionVar()
{
	cv = malloc(sizeof(conditionVar));
	sem_init(cv->semaphore, 0, 0);
	cv->waiters = 0;

	initBlockMutex();
}

void wait()
{
	__atomic_add_fetch(&(cv->waiters), 1, __ATOMIC_SEQ_CST);
	blockMutex_unlock();
	sem_wait(cv->semaphore);
	blockMutex_lock();
}

void signal()
{
	if (__atomic_load_n(&(cv->waiters), __ATOMIC_SEQ_CST) > 0)
	{
		sem_post(cv->semaphore);
		cv->waiters--;
	}
}