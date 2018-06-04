/*
 * This source file implements an alternative puts() function, that ignores its
 * input and outputs a different string. This library file is used to 
 * demonstrate preloading of shared objects.
 */
#include <stdio.h>

int puts(const char *str) {
  return printf("We took control over your C library!\n");
}