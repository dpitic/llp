/*
 * This program provides a simple example of condition variables.
 */
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/* Initialise condition variable */
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m;

bool sent = false;

void *t1_impl(void *arg) {
  pthread_mutex_lock(&m);
  puts("Thread 1 before wait");

  /*
   * Loop here is used to handle spurious wake-ups and ensure the thread does
   * not proceed until sent is true. Therefore, multiple calls to wait on the
   * condition variable will occur due to spurious wake-ups.
   */
  while (!sent) {
    pthread_cond_wait(&condvar, &m);	/* unlock mutex and block thread */
    /* On return, lock mutex again */
  }

  puts("Thread 1 after wait");
  pthread_mutex_unlock(&m);
  return NULL;
}

void *t2_impl(void *arg) {
  pthread_mutex_lock(&m);
  puts("Thread 2 before signal");

  sent = true;
  pthread_cond_signal(&condvar);	/* unblock waiting thread */

  puts("Thread 2 after signal");
  pthread_mutex_unlock(&m);
  return NULL;
}

int main(void) {
  pthread_t t1, t2;

  pthread_mutex_init(&m, NULL);
  pthread_create(&t1, NULL, t1_impl, NULL);
  sleep(2);
  pthread_create(&t2, NULL, t2_impl, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&m);
  return 0;
}
