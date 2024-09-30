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

// struct
extern char *ptrFileName;
extern pthread_t threadAudioVorbis;
extern pthread_t threadVideoTheora;
extern pthread_mutex_t hashmapMutex;
extern int counter;

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
void initTextureMutex();
void destroyTextureMutex();
//
// ---------------------
void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
