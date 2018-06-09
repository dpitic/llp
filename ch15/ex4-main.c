/*
 * This program demonstrates mixing C and assembly language. The main file is
 * written in C and calls a function defined in a dynamic library written 
 * in assembly. It also references a character string defined in the dynamic
 * library. The easiest way to link with the standard C library is to use GCC
 * for the static link phase.
 */
#include <stdio.h>

extern int sofun(void);
extern const char sostr[];

int main(void) {
  printf("%d\n", sofun());
  puts(sostr);
  return 0;
}
