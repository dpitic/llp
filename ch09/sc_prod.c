/*
 * This program calculates the scalar product of two vectors of integers.
 */
#include <stdio.h>

/* Global arrays */
const int x[] = {1, 2, 3, 4, 5};
const int y[] = {5, 4, 3, 2, 1};

/**
 * @brief      Calculate the scalar product of two integer vectors.
 *
 * @param[in]  a     First integer vector.
 * @param[in]  b     Second integer vector.
 * @param[in]  sz    The size of the vectors.
 *
 * @return     Scalar product of the two vectors as an integer.
 */
int scalar(const int a[], const int b[], size_t sz) {
  size_t i;    /* array index */
  int res = 0; /* scalar product result */

  for (i = 0; i < sz; ++i) {
    res += a[i] * b[i];
  }
  return res;
}

int main(void) {
  printf("The scalar product is: %d\n", scalar(x, y, sizeof(x) / sizeof(*x)));
  return 0;
}
