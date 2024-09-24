// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>
// #define NUMBERTHREADS 11
// void *showHello() {
//   printf("Hello world !\n");
//   return NULL;
// }
// void *showDone() {
//
//   printf("Done !\n");
//   return NULL;
// }
// int main() {
//   pthread_t threads[NUMBERTHREADS];
//   pthread_create(&threads[NUMBERTHREADS - 1], NULL, showDone, NULL);
//   for (int i = 0; i < NUMBERTHREADS - 1; i++) {
//     pthread_create(&threads[i], NULL, showHello, NULL);
//   }
//   pthread_join(threads[NUMBERTHREADS - 1], NULL);
//   for (int i = 0; i < NUMBERTHREADS - 1; i++) {
//     pthread_join(threads[i], NULL);
//   }
//   // pthread_create(&threads[0], NULL, showHello, NULL);
//   // pthread_create(&threads[1], NULL, showDone, NULL);
//   // pthread_join(threads[0], NULL);
//   // pthread_join(threads[1], NULL);
//   return 0;
// }
// ------------------------------- exercice part 2 ----------------
#include "monitor.h"
#include <string.h>
#define HELLOWORLDLENGTH 13
#define DONELENGTH 6
int main() {
  pthread_t threads[NUMBERTHREADS];
  setMonitor();
  char *message = malloc(sizeof(char) * DONELENGTH);
  strcpy(message, "Done\n");
  pthread_create(&threads[NUMBERTHREADS - 1], NULL, decrementCounter, message);
  for (int i = 0; i < NUMBERTHREADS - 1; i++) {
    char *message = malloc(sizeof(char) * HELLOWORLDLENGTH);
    strcpy(message, "Hello world\n");
    pthread_create(&threads[i], NULL, incrementCounter, message);
  }
  pthread_join(threads[NUMBERTHREADS - 1], NULL);
  for (int i = 0; i < NUMBERTHREADS - 1; i++) {
    pthread_join(threads[i], NULL);
  }
  removeMonitor();
  return 0;
}
