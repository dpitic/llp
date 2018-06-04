/*
 * This program calls the puts() function to output a string to stdio. It is
 * compiled and linked in the standard way and if executed performs as expected,
 * calling the standard C library puts() function.
 * 
 * However, if the LD_PRELOAD environment variable is set to the custom shared
 * object that implements the puts() function, the dynamic loader will load that
 * function instead of the standard C library function. The program is not
 * linked against the custom shared object library.
 * 
 * To observe these effects, first launch the program as normal, and it will
 * output the string as expected, using the standard C library function.
 * 
 * To use the custom dynamic shared object library, export the LD_PRELOAD
 * environment variable and run the program again.  This time, it will use the
 * custom library verison of puts(), which will output a different string.
 *   $ export LD_PRELOAD=$PWD/prelib.so
 */
#include <stdio.h>

int main(void) {
  puts("Hello, world!");
  return 0;
}