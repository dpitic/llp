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
  printf("%X\n", test.integer);   /* AA BB CC DD */
  /* test.shorts[0] = FF FF CC DD; test.shorts[1] = FF FF AA BB */
  printf("%X and %X\n", test.shorts[0], test.shorts[1]);
  return 0;
}