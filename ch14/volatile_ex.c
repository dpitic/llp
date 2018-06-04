/*
 * This program is used to study the effect of the volatile keyword.
 */
#include <stdio.h>

int main(void) {
  int ordinary = 0;
  volatile int vol = 4;
  ordinary++;
  vol++;
  printf("%d\n", ordinary);
  printf("%d\n", vol);
  return 0;
}
