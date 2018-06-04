/*
 * Implementation of dynamic library example function. This library is used to
 * study the shared object:
 *   $ objdump -D -Mintel-mnemonic dynlib.so
 */
#include <stdio.h>

/* Declaration of global variable in dynamic library. */
extern int global;

/* Definition of function provided by dynamic library. */
void libfun(int value) {
  printf("param: %d\n", value);
  printf("global: %d\n", global);
}
