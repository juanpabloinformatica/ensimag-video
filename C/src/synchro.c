#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>

/* les variables pour la synchro, ici */

char *ptrFileName;

// Threads
pthread_t threadAudioVorbis;
pthread_t threadVideoTheora;

// Mutex
pthread_mutex_t hashmapMutex;

// Monitors
Monitor *monitorWindow;
Monitor *monitorTexture;
// last prodcuer consumer
pthread_mutex_t textureMutex;
pthread_cond_t producerAdvertiseConsumer;
pthread_cond_t consumerAdvertiseProducer;
int counter = 0;

/* l'implantation des fonctions de synchro ici */
// ------ mine -------
void initHashmapMutex() { pthread_mutex_init(&hashmapMutex, NULL); }
void destroyHashmapMutex() { pthread_mutex_destroy(&hashmapMutex); }
void lockHashmapMutex() { pthread_mutex_lock(&hashmapMutex); }
void unlockHashmapMutex() { pthread_mutex_unlock(&hashmapMutex); }

void initMonitors() {
  monitorWindow = malloc(sizeof(Monitor));
  monitorTexture = malloc(sizeof(Monitor));
  pthread_cond_init(&monitorWindow->condition, NULL);
  pthread_cond_init(&monitorTexture->condition, NULL);
  pthread_mutex_init(&monitorWindow->mutex, NULL);
  pthread_mutex_init(&monitorTexture->mutex, NULL);
  monitorWindow->conditionAchieved = false;
  monitorTexture->conditionAchieved = false;
}
void destroyMonitors() {
  pthread_cond_destroy(&monitorWindow->condition);
  pthread_cond_destroy(&monitorTexture->condition);
  pthread_mutex_destroy(&monitorWindow->mutex);
  pthread_mutex_destroy(&monitorTexture->mutex);
  free(monitorWindow);
  free(monitorTexture);
}
void initTextureMutex() { pthread_mutex_init(&textureMutex, NULL); }
void destroyTextureMutex() { pthread_mutex_destroy(&textureMutex); }

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
  while (counter == 0) {
    pthread_cond_wait(&producerAdvertiseConsumer, &textureMutex);
  }
}
void finConsommerTexture() {
  counter--;
  pthread_mutex_unlock(&textureMutex);
  pthread_cond_signal(&consumerAdvertiseProducer);
}
void debutDeposerTexture() {
  while (counter > NBTEX - 1) {
    pthread_cond_wait(&consumerAdvertiseProducer, &textureMutex);
  }
}
void finDeposerTexture() {
  counter++;
  pthread_mutex_unlock(&textureMutex);
  pthread_cond_signal(&producerAdvertiseConsumer);
}
