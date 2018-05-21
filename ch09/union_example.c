/*
 * This program demonstrates union types and little endian on Intel x86.
 */
#include <stdio.h>

union dword {
  int integer;      /* 4 bytes */
  short shorts[2];  /* 2 x 2 byte array elements */
};

int main(int argc, char const *argv[])
{
  union dword test;
  test.integer = 0xAABBCCDD;
  printf("%x\n", test.integer);
  printf("%x and %x\n", test.shorts[0], test.shorts[1]);
  return 0;
}