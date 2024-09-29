#include "ensivideo.h"
#include "synchro.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "oggstream.h"
#include "stream_common.h"

int main(int argc, char *argv[]) {
  int res;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE", argv[0]);
    exit(EXIT_FAILURE);
  }
  assert(argc == 2);

  // Initialisation de la SDL
  res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
  atexit(SDL_Quit);
  assert(res == 0);

  // Your code HERE
  // everything is defined in synchro.h
  ptrFileName = argv[1];
  initMonitors();
  initSemaphores();
  initMutexTexture();
  initHashmapMutex();
  printf("%s", ptrFileName);
  // start the two stream readers (theoraStreamReader and vorbisStreamReader)
  // each in a thread
  pthread_create(&threadAudioVorbis, NULL, vorbisStreamReader, ptrFileName);
  pthread_create(&threadVideoTheora, NULL, theoraStreamReader, ptrFileName);
  // // wait for vorbis thread
  pthread_join(threadAudioVorbis, NULL);

  // 1 seconde of sound in advance, thus wait 1 seconde
  // before leaving
  sleep(1);

  // Wait for theora and theora2sdl threads
  // pthread_cancel()
  // pthread_cancel()
  //
  pthread_join(threadVideoTheora, NULL);
  pthread_join(showThread, NULL);
  // SDL_Quit();
  // TODO
  /* liberer des choses ? */
  destroyHashmapMutex();
  destroyMutexTexture();
  destroyMonitors();
  destroySemaphores();


  exit(EXIT_SUCCESS);
}
