/*
 * This program demonstrates the use of a mutex to protect a shared variable
 * (data). The program uses two threads to increment a shared variable multiple
 * times.
 */
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m; /* mutex lock */

pthread_t t1, t2;

uint64_t value = 0;  /* global shared variable */

/**
 * @brief    Thread start function used to increment shared variable.
 *
 * @details  This function increments a shared variable for a constant 
 *           multiple times.
 *
 * @param    Not used.
 *
 * @return   NULL. The result is set in the global variable value.
 */
void *impl1(void *arg) {
  for (int n = 0; n < 10000000; n++) {
    pthread_mutex_lock(&m);
    value += 1;
    pthread_mutex_unlock(&m);
  }
  return NULL;
}

int main(void) {
  pthread_mutex_init(&m, NULL);

  pthread_create(&t1, NULL, impl1, NULL);
  pthread_create(&t2, NULL, impl1, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%" PRIu64 "\n", value);

  pthread_mutex_destroy(&m);
  return 0;
}
