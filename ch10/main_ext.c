/*
 * This program defines a global variable declared as extern in another file
 * and calls a function defined in another file;
 */
#include <stdio.h>

int z = 0;         /* declared extern in another file */
int square(int x); /* forward declaration */

int main(void) {
  printf("%d\n", square(5));
  return 0;
}
