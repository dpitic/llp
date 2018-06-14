/*
 * This program demonstrates calling an assembly function that uses SIMD
 * instructions.
 */
#include <stdio.h>
#include <stdlib.h>

/* Assembly language function */
extern void sse(float[static 4], float[static 4]);

int main(void) {
  float x[4] = {1.0f, 2.0f, 3.0f, 4.0f};
  float y[4] = {5.0f, 6.0f, 7.0f, 8.0f};

  sse(x, y);

  printf("%f %f %f %f\n", x[0], x[1], x[2], x[3]);
  return 0;
}
