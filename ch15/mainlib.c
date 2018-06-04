/*
 * This program implements the main() function used to demonstrate
 * implementation of dynamic library in C.
 */

/* Forward declaration for function provided by dynamic library. */
extern void libfun(int value);

/* Definition of global variable declared in dynamic library. */
int global = 100;

int main(void) {
  libfun(42);
  return 0;
}
