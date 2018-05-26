/*
 * This program demonstrates usage of dynamically allocated memory.
 */
#include <malloc.h>
#include <stdio.h>

/**
 * @brief      Input integers.
 *
 * @param      out_count  Number of elements.
 *
 * @return     Pointer to memory containing elements.
 */
int *array_read(size_t *out_count) {
  int *array;
  size_t i;
  size_t cnt;
  printf("Enter number of elements: ");
  scanf("%zu", &cnt);
  array = malloc(cnt * sizeof(int));

  printf("Enter element values:\n");
  for (i = 0; i < cnt; i++) {
    scanf("%d", &array[i]);
  }
  *out_count = cnt;
  return array;
}

/**
 * @brief      Output the elements in the given array to stdout.
 *
 * @param      array  Pointer to the array.
 * @param[in]  count  Number of elements in the array.
 */
void array_print(int const *array, size_t count) {
  size_t i;

  for (i = 0; i < count; i++) {
    printf("%d ", array[i]);
  }
  puts("");
}

/**
 * @brief      Calculate the sum of the elements in the given array.
 *
 * @param      array  Pointer to the array.
 * @param[in]  count  Number of elements in the array.
 *
 * @return     Sum of the elements in the array.
 */
int array_sum(int const *array, size_t count) {
  size_t i;
  int sum = 0;
  for (i = 0; i < count; i++) {
    sum += array[i];
  }
  return sum;
}

int main(int argc, char const *argv[]) {
  int *array;
  size_t count;

  array = array_read(&count);
  array_print(array, count);
  printf("Sum is: %d\n", array_sum(array, count));
  free(array);
  return 0;
}