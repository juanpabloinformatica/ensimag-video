#include "synchro.h"
#include "ensitheora.h"

/* les variables pour la synchro, ici */

char *ptrFileName;

// Threads
pthread_t threadAudioVorbis;
pthread_t threadVideoTheora;
pthread_t showThread;

// Mutex
pthread_mutex_t hashmapMutex;

// Monitors
MonitorWindow *monitorWindow;
MonitorTexture *monitorTexture;
MonitorDebutTexture *monitorDebutTexture;
MonitorFinTexture *monitorFinTexture;
/* l'implantation des fonctions de synchro ici */
// ------ mine -------
void initHashmapMutex() { pthread_mutex_init(&hashmapMutex, NULL); }
void destroyHashmapMutex() { pthread_mutex_destroy(&hashmapMutex); }
void lockHashmapMutex() { pthread_mutex_lock(&hashmapMutex); }
void unlockHashmapMutex() { pthread_mutex_unlock(&hashmapMutex); }
void initMonitors() {
  monitorWindow = malloc(sizeof(MonitorWindow));
  monitorTexture = malloc(sizeof(MonitorWindow));
  monitorDebutTexture = malloc(sizeof(MonitorWindow));
  monitorFinTexture = malloc(sizeof(MonitorWindow));
  pthread_cond_init(&monitorWindow->windowCondition, NULL);
  pthread_cond_init(&monitorTexture->textureCondition, NULL);
  pthread_cond_init(&monitorDebutTexture->textureDebutCondition, NULL);
  pthread_cond_init(&monitorFinTexture->textureFinCondition, NULL);
  pthread_mutex_init(&monitorWindow->windowMutex, NULL);
  pthread_mutex_init(&monitorTexture->textureMutex, NULL);
  pthread_mutex_init(&monitorDebutTexture->textureDebutMutex, NULL);
  pthread_mutex_init(&monitorFinTexture->textureFinMutex, NULL);
}
void destroyMonitors() {
  pthread_cond_destroy(&monitorWindow->windowCondition);
  pthread_cond_destroy(&monitorTexture->textureCondition);
  pthread_cond_destroy(&monitorDebutTexture->textureDebutCondition);
  pthread_cond_destroy(&monitorFinTexture->textureFinCondition);
  pthread_mutex_destroy(&monitorWindow->windowMutex);
  pthread_mutex_destroy(&monitorTexture->textureMutex);
  pthread_mutex_destroy(&monitorDebutTexture->textureDebutMutex);
  pthread_mutex_destroy(&monitorFinTexture->textureFinMutex);
  free(monitorWindow);
  free(monitorTexture);
  free(monitorDebutTexture);
  free(monitorFinTexture);
}

// ------ mine -------
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
  printf("%p", &buffer);
  pthread_mutex_lock(&monitorWindow->windowMutex);
  windowsx = buffer[0].width;
  windowsy = buffer[0].height;
  monitorWindow->windowSet = true;
  printf("fenetre set");
  pthread_mutex_unlock(&monitorWindow->windowMutex);
  pthread_cond_signal(&monitorWindow->windowCondition);
}

void attendreTailleFenetre() {
  while (monitorWindow->windowSet == false) {
    printf("waiting for window");
    pthread_cond_wait(&monitorWindow->windowCondition,
                      &monitorWindow->windowMutex);
  }
}

void signalerFenetreEtTexturePrete() {}

void attendreFenetreTexture() {}

void debutConsommerTexture() {}

void finConsommerTexture() {}

void debutDeposerTexture() {}

void finDeposerTexture() {}
