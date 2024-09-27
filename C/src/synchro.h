#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "ensitheora.h"
#include <pthread.h>
#include <stdbool.h>

/* Les extern des variables pour la synchro ici */
typedef struct MonitorWindow MonitorWindow;
struct MonitorWindow {
  pthread_cond_t windowCondition;
  pthread_mutex_t windowMutex;
  bool windowSet;
};
typedef struct MonitorTexture MonitorTexture;
struct MonitorTexture {
  pthread_cond_t textureCondition;
  pthread_mutex_t textureMutex;
  bool textureSet; // as boolean
};
typedef struct MonitorDebutTexture MonitorDebutTexture;
struct MonitorDebutTexture {
  pthread_cond_t textureDebutCondition;
  pthread_mutex_t textureDebutMutex;
  bool textureDebutSet; // as boolean
};
typedef struct MonitorFinTexture MonitorFinTexture;
struct MonitorFinTexture {
  pthread_cond_t textureFinCondition;
  pthread_mutex_t textureFinMutex;
  bool textureFinSet; // as boolean
};

extern MonitorWindow *monitorWindow;
extern MonitorTexture *monitorTexture;
extern MonitorDebutTexture *monitorDebutTexture;
extern MonitorFinTexture *monitorFinTexture;


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
