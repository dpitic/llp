/*
 * This program demonstrates how to create threads using POSIX threads
 * (pthreads).
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Thread start routine */
void *threadimpl(void *arg) {
  for (int i = 0; i < 10; i++) {
    puts(arg);
    sleep(1);
  }
  return NULL;
}

int main(void) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, threadimpl, "fizz");
  pthread_create(&t2, NULL, threadimpl, "buzzzz");
  pthread_exit(NULL); /* main() termination; subsequent code won't execute */
  puts("bye");        /* this will not be output */
  return 0;
}
