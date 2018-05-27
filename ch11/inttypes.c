/*
 * This program demonstrates the C99 platform independent types.
 */
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
  int64_t i64 = -10;
  uint64_t u64 = 100;
  printf("Signed 64-bit integer:   %" PRIi64 "\n", i64);
  printf("Unsigned 64-bit integer: %" PRIu64 "\n", u64);
  return 0;
}
