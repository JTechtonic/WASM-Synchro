#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdatomic.h>
#include <stdlib.h>


typedef volatile struct {
    volatile atomic_int sem_val;
} semaphore;

static semaphore* globalSem;

void semaphore_init();
void semaphore_wait();
void semaphore_post();

#endif