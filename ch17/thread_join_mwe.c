/*
 * This program demonstrates thread synchronisation using thread_join().
 */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief    Thread start routine.
 *
 * @details  Outputs the string parameter 3 times with 1 second sleep between.
 *
 * @param    String parameter to output to stdio.
 * @return   Void pointer pointing to the completion message string.
 */
void *worker(void *param) {
  for (int i = 0; i < 3; i++) {
    puts((const char*)param);
    sleep(1);
  }
  return (void*)"done";
}

int main(void)
{
  pthread_t t;
  void *result;

  pthread_create(&t, NULL, worker, (void *)"I am a worker!");
  pthread_join(t, &result);
  puts((const char*)result);
  return 0;
}
