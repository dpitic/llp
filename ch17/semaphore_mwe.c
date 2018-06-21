/*
 * This program demonstrates semaphore usage.
 */
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;	/* semaphore */

/* Global thread counters */
uint64_t counter1 = 0;
uint64_t counter2 = 0;

pthread_t t1, t2, t3;

/**
 * @brief    Thread start function used to increment global counter1.
 *
 * @details  This function increments global counter1 and increments a semaphore
 *           when finished.
 *
 * @param    Not used.
 * @return   NULL. Global counter1 is incremented a constant number of times.
 */
void *t1_impl(void *arg) {
  while (counter1 < 10000000) {
    counter1++;
  }
  sem_post(&sem);
  return NULL;
}

/**
 * @brief    Thread start function used to increment global counter2.
 *
 * @details  This function increments global counter2 and increments a semaphore
 *           when finished.
 *
 * @param    Not used.
 * @return   NULL. Global Counter2 is incremented a constant number of times.
 */
void *t2_impl(void *arg) {
  while (counter2 < 20000000) {
    counter2++;
  }
  sem_post(&sem);
  return NULL;
}

/**
 * @brief    Thread start function that outputs the value of two counters to
 *           stdout.
 *
 * @details  This thread start function waits for two threads to finish
 *           incrementing their respective counters, and then outputs the values
 *           of those counters to stdout. This thread blocks on a semaphore and
 *           waits for the other two worker threads to complete incrementing
 *           their counters.
 *
 * @param    Not used.
 * @return   Null.
 */
void *t3_impl(void *arg) {
  sem_wait(&sem); /* wait until the other two threads have finished */
  sem_wait(&sem);
  /* The other two threads have finished; counters are set */
  printf("End: counter1 = %" PRIu64 " counter2 = %" PRIu64 "\n", counter1,
         counter2);
  return NULL;
}

int main(void) {
  sem_init(&sem, 0, 0); /* initialise a process-local semaphore */
  pthread_create(&t3, NULL, t3_impl, NULL);

  sleep(1);
  pthread_create(&t1, NULL, t1_impl, NULL);
  pthread_create(&t2, NULL, t2_impl, NULL);

  sem_destroy(&sem);
  pthread_exit(NULL);	/* wait for all threads for finish */
  return 0;
}
