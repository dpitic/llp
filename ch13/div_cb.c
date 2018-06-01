/*
 * This program demonstrates the use of callback functions to handle errors.
 */
#include <stdio.h>

int div(int x, int y, void(on_error)(int, int)) {
  if (y != 0) {
    return x / y;
  } else {
    on_error(x, y);
    return 0;
  }
}

static void div_by_zero(int x, int y) {
  fprintf(stderr, "Division by zero: %d / %d\n", x, y);
}

int main(int argc, char const *argv[]) {
  printf("%d %d\n", div(10, 2, div_by_zero), div(10, 0, div_by_zero));
  return 0;
}