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

/**
 * @brief    Calculate number of factors in first half of range.
 *
 * @details  This thread worker iterates over the first half of the range of
 *           numbers to calculate the number of factors in that half.
 *
 * @param    Not used. Number for which to calculate the number of factors is
 *           provided by the global variable input.
 * @return   NULL. The number of factors is provided in the global variable
 *           result1.
 */
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
/**
 * @brief    Calculate the number of factors in the second half of the range.
 *
 * @details  This thread worker iterates over the second half of the range of
 *           numbers to calculate the number of factors in that half.
 *
 * @param    Not used. Number for which to calculate the number of factors is
 *           is provided by the global variable input.
 * @return   NULL. The number of factors is provided in the global variable
 *           result 2.
 */
void *fact_worker2(void *arg) {
  result2 = 0;
  for (uint64_t i = input / 2; i <= input; i++) {
    if (input % i == 0) {
      result2++;
    }
  }
  return NULL;
}
/**
 * @brief    Calculate the number of factors of the given number.
 *
 * @details  This function calculates the number of factors of the given number
 *           by using two threads which calculate the number of factors in both
 *           halves of the number range.
 *
 * @param    num is the number for which to calculate the number of factors.
 * @return   Number of factors for the given number.
 */
uint64_t factors_mp(uint64_t num) {
  input = num;
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, fact_worker1, NULL); /* first half range */
  pthread_create(&thread2, NULL, fact_worker2, NULL); /* 2nd half range */

  /* Wait for threads to finish */
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return result1 + result2;
}

int main(void) {
  uint64_t input = 2000000000;
  printf("Factors of %" PRIu64 ": %" PRIu64 "\n", input, factors_mp(input));
  return 0;
}
