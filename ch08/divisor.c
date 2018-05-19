/*
 * This program searches for the first divisor, which is then printed out.
 */
#include <stdio.h>

/**
 * @brief    Calculate the first divisor of a given integer.
 *
 * @details  This function accepts an integer argument n and searches for an
 *           integer r from 1 exclusive to n inclusive, such that n is a
 *           multiple of r. If r == n, then this is a prime number.
 *
 * @param    n is the integer for which to find the first divisor.
 * @return   First divisor for the integer n.
 */
int first_divisor(int n) {
  int i;
  if (n == 1) {
    return 1;
  }

  for (i = 2; i <= n; i++) {
    if (n % i == 0) {
      return i;
    }
  }
  return 0;
}

int main(void)
{
  int i;
  puts("num\tdivisor");
  for (i = 1; i < 11; i++) {
    printf("%d\t%d\n", i, first_divisor(i));
  }
  return 0;
}
