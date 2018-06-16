/*
 * This program calculates the number of factors of a given number, using a
 * dumbed-down implementation of multithreaded code, which always performs the
 * computations in two threads.
 */
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>

uint64_t input = 0;

int result1 = 0; /* global result of worker thread 1 */

void *fact_worker1(void *arg) {
  result1 = 0;
  for (uint64_t i = 1; i < input / 2; i++) {
    if (input % i == 0) {
      result1++;
    }
  }
  return NULL;
}

int result2 = 0; /* global result of worker thread 2 */

void *fact_worker2(void *arg) {
  result2 = 0;
  for (uint64_t i = input / 2; i <= input; i++) {
    if (input % i == 0) {
      result2++;
    }
  }
  return NULL;
}

uint64_t factors_mp(uint64_t num) {
  input = num;
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, fact_worker1, NULL);
  pthread_create(&thread2, NULL, fact_worker2, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return result1 + result2;
}

int main(void) {
  uint64_t input = 2000000000;
  printf("Factors of %" PRIu64 ": %" PRIu64 "\n", input, factors_mp(input));
  return 0;
}
