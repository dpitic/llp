/*
 * This program checks whether the number input by the user is a prime number.
 */
#include <stdio.h>

/**
 * @brief    Determine whether the given integer is a prime number.
 *
 * @param    n  Integer to check.
 * @return   1 if n is a prime number, 0 otherwise.
 */
int is_prime(unsigned long n) {
  unsigned long i; /* loop index */

  if (n < 2UL) {
    return 0;
  }
  if (n == 2UL) {
    return 1; /* first prime number */
  }

  for (i = 2UL; i < n / 2UL + 1UL; i++) {
    if (!(n % i)) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  unsigned long n = 0UL;

  while (!scanf("%lu", &n)) {
    ;
  }
  printf("%lu is %sprime\n", n, is_prime(n) ? "" : "not ");
  return 0;
}
