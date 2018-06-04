/*
 * This program is used to study printf() vulnerability. Launch the program
 * providing 9 "%x" format specifiers:
 *   $ ./printf_vuln <<< "%x %x %x %x %x %x %x %x %x"
 */
#include <stdio.h>

int main(void)
{
  char buffer[1024];
  gets(buffer);
  printf(buffer);
  return 0;
}
