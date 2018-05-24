/*
 * This is the main function that calls the square() function defined in another
 * file. The program is used to demonstrate calling code from other files.
 */
#include <stdio.h>

int square(int); /* forward declaration */

int main(void) {
  printf("%d\n", square(5));
  return 0;
}
