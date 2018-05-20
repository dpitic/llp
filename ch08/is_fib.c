/*
 * This program outputs the first 10 integers from 1 to 10, inclusive, and 
 * indicates whether they are part of the Fibonacci series.
 */
#include <stdio.h>

/**
 * @brief      Determine whether the given integer is a Fibonacci Number.
 * 
 * @details    The first two numbers in the Fibonacci series is f[1] = 1 and 
 *             f[2] = 1. A Fibonacci number is the sum of two previous numbers
 *             in the series: f[n] = f[n-1] + f[n-2]
 *
 * @param[in]  n     Candidate integer to check if it is a Fibonacci number.
 *
 * @return     1 if n is a Fibonacci number, otherwise 0.
 */
int is_fib(int n) {
  /*
   * This function implements a straightforward (though not necessarily optimal)
   * algorithm for calculating whether a number n is a Fibonacci number. It
   * calculates all Fibonacci numbers in the series up to n. If a number greater
   * than n was calculated and n has not been enumerated, then n is not a
   * Fibonacci number. If the last element calculated is n, then n is a 
   * Fibonacci number.
   */
  int a = 1;    /* f[1] = 1; this will also be f[n-1] */
  int b = 1;    /* f[2] = 1; this will also be f[n-2] */

  if (n == 1)
  {
    return 1;   /* f[1] = 1 */
  }

  while (a <= n && b <= n) {
    int t = b;

    if (n == a || n == b) {
      return 1;
    }
    b = a;
    a = t + a;
  }
  return 0;
} /* is_fib() */

/**
 * @brief      Check whether the given integer is a Fibonacci number.
 * 
 * @details    Output a message to stdout stating whether the given integer is
 *             a Fibonacci number (1), or not (0).
 *
 * @param[in]  n     Candidate integer to check.
 */
void check(int n) {
  printf("%d\t-> %d\n", n, is_fib(n));
}

int main(int argc, char const *argv[])
{
  int i;
  for (i = 1; i < 11; i++)
  {
    check(i);
  }
  return 0;
}