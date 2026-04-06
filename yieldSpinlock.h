#ifndef _YIELDSPINLOCK_H_
#define _YIELDSPINLOCK_H_

#include "spinlock.h"
#include <sched.h>

static int* global_yieldSpinlock;

void initYieldSpinlocks();
void yieldSpinlock_lock();
void yieldSpinlock_unlock();

#endif