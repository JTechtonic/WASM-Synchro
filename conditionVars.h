#ifndef _CONDITIONVARS_H_
#define _CONDITIONVARS_H_

#include "blockMutex.h"
#include <semaphore.h>
#include <stdlib.h>

typedef struct cond_t {
	sem_t* semaphore;
	int waiters;
} conditionVar;

static conditionVar* cv;

void initConditionVar();
void wait();
void signal();

#endif