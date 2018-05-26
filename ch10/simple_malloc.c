/*
 * This code snippet demonstrates simple use of malloc() to dynamically allocate
 * memory on the heap.
 */
#include <malloc.h>

int main(int argc, char const *argv[]) {
  int *array;

  /*
   * malloc() returns a void pointer to the allocated memory starting address.
   * Its argument is the byte size, elements count multiplied by element size.
   */
  array = malloc(10 * sizeof(int));

  /* use array here */

  free(array); /* release the allocated memory */

  return 0; /* dynamically allocated memory is released when program exits */
}