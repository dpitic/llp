/*
 * This program demonstrates how to unwind the stack and display the frame
 * pointer address for all functions launched when unwind() gets called. This
 * should be compiled with -O0 to prevent optimisations. Also compile with the
 * GCC option -fomit-frame-pointer.
 */
void unwind(); /* forward declaration for assembly function */
int *fptr;     /* global pointer to a local variable in main() */
void f(int count) {
  if (count) {
    f(count - 1);
  } else {
    unwind();
  }
}

int main(void) {
  int filler = 0; /* make a local variable in main() */
  fptr = &filler; /* define the global pointer for unwind */
  f(10);
  return 0;
}
