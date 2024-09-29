#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>

/* les variables pour la synchro, ici */

char *ptrFileName;

// Threads
pthread_t threadAudioVorbis;
pthread_t threadVideoTheora;
pthread_t showThread;

// Mutex
pthread_mutex_t hashmapMutex;

// Monitors
Monitor *monitorWindow;
Monitor *monitorTexture;
Monitor *monitorDebutTexture;
Monitor *monitorFinTexture;
sem_t empty;
sem_t full;
pthread_mutex_t mutexTexture;

/* l'implantation des fonctions de synchro ici */
// ------ mine -------
void initHashmapMutex() { pthread_mutex_init(&hashmapMutex, NULL); }
void destroyHashmapMutex() { pthread_mutex_destroy(&hashmapMutex); }
void lockHashmapMutex() { pthread_mutex_lock(&hashmapMutex); }
void unlockHashmapMutex() { pthread_mutex_unlock(&hashmapMutex); }
void initMonitors() {
  monitorWindow = malloc(sizeof(Monitor));
  monitorTexture = malloc(sizeof(Monitor));
  monitorDebutTexture = malloc(sizeof(Monitor));
  monitorFinTexture = malloc(sizeof(Monitor));
  pthread_cond_init(&monitorWindow->condition, NULL);
  pthread_cond_init(&monitorTexture->condition, NULL);
  pthread_cond_init(&monitorDebutTexture->condition, NULL);
  pthread_cond_init(&monitorFinTexture->condition, NULL);
  pthread_mutex_init(&monitorWindow->mutex, NULL);
  pthread_mutex_init(&monitorTexture->mutex, NULL);
  pthread_mutex_init(&monitorDebutTexture->mutex, NULL);
  pthread_mutex_init(&monitorFinTexture->mutex, NULL);
  monitorWindow->conditionAchieved = false;
  monitorTexture->conditionAchieved = false;
  monitorDebutTexture->conditionAchieved = false;
  monitorFinTexture->conditionAchieved = false;
}
void destroyMonitors() {
  pthread_cond_destroy(&monitorWindow->condition);
  pthread_cond_destroy(&monitorTexture->condition);
  pthread_cond_destroy(&monitorDebutTexture->condition);
  pthread_cond_destroy(&monitorFinTexture->condition);
  pthread_mutex_destroy(&monitorWindow->mutex);
  pthread_mutex_destroy(&monitorTexture->mutex);
  pthread_mutex_destroy(&monitorDebutTexture->mutex);
  pthread_mutex_destroy(&monitorFinTexture->mutex);
  free(monitorWindow);
  free(monitorTexture);
  free(monitorDebutTexture);
  free(monitorFinTexture);
}
void initMutexTexture() { pthread_mutex_init(&mutexTexture, NULL); }
void destroyMutexTexture() { pthread_mutex_destroy(&mutexTexture); }
void initSemaphores() {
  sem_init(&empty, 0, NBTEX);
  sem_init(&full, 0, 0);
}
void destroySemaphores() {
  sem_destroy(&empty);
  sem_destroy(&full);
}

// ------ mine -------
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
  printf("%p", &buffer);
  pthread_mutex_lock(&monitorWindow->mutex);
  windowsx = buffer[0].width;
  windowsy = buffer[0].height;
  monitorWindow->conditionAchieved = true;
  printf("Window set");
  pthread_mutex_unlock(&monitorWindow->mutex);
  pthread_cond_signal(&monitorWindow->condition);
}

void attendreTailleFenetre() {
  while (monitorWindow->conditionAchieved == false) {
    printf("waiting for window");
    pthread_cond_wait(&monitorWindow->condition, &monitorWindow->mutex);
  }
}

void signalerFenetreEtTexturePrete() {
  monitorTexture->conditionAchieved = true;
  pthread_cond_signal(&monitorTexture->condition);
}

void attendreFenetreTexture() {
  while (monitorTexture->conditionAchieved == false) {
    printf("waiting for texture + window");
    pthread_cond_wait(&monitorTexture->condition, &monitorTexture->mutex);
  }
}
void debutConsommerTexture() {
  while (monitorDebutTexture->conditionAchieved == false) {
    pthread_cond_wait(&monitorDebutTexture->condition,
                      &monitorDebutTexture->mutex);
  }
  // sem_wait(&full);
  // pthread_mutex_lock(&mutexTexture);
}

void finConsommerTexture() {
  // pthread_mutex_unlock(&mutexTexture);
  // sem_post(&empty);
}

void debutDeposerTexture(int text_iwri) {
  if (text_iwri > NBTEX) {
    pthread_mutex_lock(&monitorDebutTexture->mutex);
  } else {
    pthread_mutex_unlock(&monitorDebutTexture->mutex);
    pthread_cond_signal(&monitorDebutTexture->condition);
  }
  // sem_wait(&empty);
  // pthread_mutex_lock(&mutexTexture);
  // if(){
  //
  // }
}

void finDeposerTexture(int text_iwri) {
  debutDeposerTexture(text_iwri);
  // pthread_mutex_unlock(&mutexTexture);
  // sem_post(&full);
}
