/*
 * This program implements a simple function that calculates a maximum of two
 * values. It will be used to examine the disassembly produced by objdump:
 *   $ objdump -D -M intel-mnemonic maximum
 *   
 * GCC can be used to generate the assembly output:
 *   $ gcc -ansi -Wall -S -masm=intel maximum.c
 */

int maximum(int a, int b) {
  char buffer[4096];
  if (a < b) {
    return b;
  }
  return a;
}

int main(void) {
  int x = maximum(42, 999);
  return 0;
}
