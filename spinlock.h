#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include <stdbool.h>
#include <stdatomic.h>

#define SPINLOCK_LOCKED 1
#define SPINLOCK_UNLOCKED 0

static _Atomic int* global_spinlock;

bool atomic_test_and_set(_Atomic int* spinlock);
void spinlock_lock(_Atomic int* spinlock);
void spinlock_unlock(_Atomic int* spinlock);
void initSpinlocks();

#endif