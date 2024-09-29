#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "ensitheora.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

/* Les extern des variables pour la synchro ici */
typedef struct Monitor Monitor;
struct Monitor {
  pthread_cond_t condition;
  pthread_mutex_t mutex;
  bool conditionAchieved;
};

extern Monitor *monitorWindow;
extern Monitor *monitorTexture;
extern Monitor *monitorDebutTexture;
extern Monitor *monitorFinTexture;
extern sem_t empty;
extern sem_t full;
extern pthread_mutex_t mutexTexture;

// struct
extern char *ptrFileName;
extern pthread_t threadAudioVorbis;
extern pthread_t threadVideoTheora;
extern pthread_t showThread;
extern pthread_mutex_t hashmapMutex;

// provided ensimag
extern bool fini;

/* Fonctions de synchro à implanter */

// ------ mine -------
// 5.2 start
void initHashmapMutex();
void destroyHashmapMutex();
void lockHashmapMutex();
void unlockHashmapMutex();
// 5.2 finish
void initMonitors();
void destroyMonitors();
//
void initSemaphores();
void destroySemaphores();
void initMutexTexture();
void destroyMutexTexture();
//

// ---------------------
void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture(int text_iwri);
void finDeposerTexture(int text_iwri);

#endif
