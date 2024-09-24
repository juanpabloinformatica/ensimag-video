#ifndef __MONITOR__
#define __MONITOR__
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define NUMBERTHREADS 11
typedef struct Monitor Monitor;
struct Monitor {
  int counter;
  pthread_mutex_t lockCounter;
  pthread_cond_t lockCounterCondition;
};
extern Monitor *monitor;
void setMonitor();
void removeMonitor();
void *incrementCounter(void* args);
void *decrementCounter(void* args);
#endif
