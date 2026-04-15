#ifndef _BLOCKMUTEX_H_
#define _BLOCKMUTEX_H_

#include <stdbool.h>

#define MUTEX_LOCKED 1
#define MUTEX_UNLOCKED 0

static int* globalBlockMutex;

void initBlockMutex();
void blockMutex_lock();
void blockMutex_unlock();

#endif