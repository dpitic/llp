/*
 * This program demonstrates the race condition developed when multiple threads
 * modify a shared variable (data). It has two threads that increment a shared
 * variable multiple times. The output will be different every time the program
 * is run. The program should be compiled with optimisations disabled, or the
 * shared variable should be marked volatile, to prevent the incrementing loop
 * from being transformed into a single `value += 10000000` statement.
 *   $ gcc -O0 -pthread -o mutex_ex_counter_bad mutex_counter_bad.c
 */
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2;

/* Prevent the incrementing loop from being optimised. */
volatile uint64_t value = 0;

/**
 * @brief    Thread start function used to increment global shared variable.
 *
 * @details  This function is executed in separate threads to increment a
 *           global shared variable a constant amount. This function is not
 *           thread safe.
 *
 * @param    Not used.
 *
 * @return   NULL. Global shared variable value is set by this function.
 */
void *impl1(void *arg) {
  for (int n = 0; n < 10000000; n++) {
    value += 1;
  }
  return NULL;
}

/*
 * This program will produce unexpected results due to a data race affecting
 * the shared global variable.
 */
int main(void) {
  pthread_create(&t1, NULL, impl1, NULL);
  pthread_create(&t2, NULL, impl1, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%" PRIu64 "\n", value);
  return 0;
}
