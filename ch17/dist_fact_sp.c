/*
 * This program demonstrates a CPU bound program which counts the factors of
 * a number. This implementation solves the problem using the most trivial
 * brute-force method on a single core.
 */
#include <inttypes.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief    Count the factors of a number.
 *
 * @details  This function implements a bruite-force method of counting the
 *           number of factors for the given number.
 *
 * @param    Number for which to determine the factors.
 * @return   Number of factors for the given number.
 */
uint64_t factors(uint64_t num) {
  uint64_t result = 0;
  for (uint64_t i = 1; i < num; i++) {
    if (num % i == 0) {
      result++;
    }
  }
  return result;
}

int main(void) {
  /* 
   * Volatile to prevent constant propagation and possibility of result being
   * computed during compilation.
   */
  volatile uint64_t input = 2000000000;
  printf("Factors of %" PRIu64 ": %" PRIu64 "\n", input, factors(input));
  return 0;
}
