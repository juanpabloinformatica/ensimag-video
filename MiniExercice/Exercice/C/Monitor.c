#include "monitor.h"
Monitor *monitor;

void setMonitor(void) {
  monitor = malloc(sizeof(Monitor));
  monitor->counter = 0;
  pthread_mutex_init(&(monitor->lockCounter), NULL);
  pthread_cond_init(&(monitor->lockCounterCondition), NULL);
}
void removeMonitor(void) {
  if (monitor != NULL) {
    pthread_cond_destroy(&monitor->lockCounterCondition);
    pthread_mutex_destroy(&monitor->lockCounter);
    free(monitor);
  }
}

void *incrementCounter(void *arg) {
  if (monitor != NULL) {
    pthread_mutex_lock(&monitor->lockCounter);
    monitor->counter++;
    pthread_mutex_unlock(&monitor->lockCounter);
    printf("%s", (char *)arg);
    pthread_cond_signal(&monitor->lockCounterCondition);
  }
  return NULL;
}
void *decrementCounter(void *arg) {
  if (monitor != NULL) {
    // while (1) {
    while (monitor->counter != NUMBERTHREADS - 1) {
      // wait signal
      pthread_cond_wait(&monitor->lockCounterCondition, &monitor->lockCounter);
      // monitor->lockCounterCondition()
    }
    printf("%s", (char *)arg);
    monitor->counter--;
    pthread_mutex_unlock(&monitor->lockCounter);
    // }
  }
  return NULL;
}
