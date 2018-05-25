/*
 * This program is used to generate an executable object that will be examined
 * using the ldd command.
 *
 *   $ ldd main_ldd
 *
 * This command will show the dynamic libraries that the object is linked with.
 */
#include <stdio.h>

int main(void) {
  printf("Hello World\n");
  return 0;
}
