/*
 * This program calculates the number of factors of a given number using an
 * arbitrary number of threads.
 */
#include <inttypes.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Number of threads to use for the calculation */
#define THREADS 4

/* This structure holds information about a single factorisation task */
struct fact_task {
  uint64_t num;      /* number for which to calculate the number of factors */
  uint64_t from, to; /* range to calculate number of factors [from, to) */
  uint64_t result;   /* number of factors of num in this range */
};

/**
 * @brief    Calculate the number of factors of a number in the given range.
 *
 * @details  This is a worker thread start function that iterates over the
 *           range of numbers provided in the task structure and calculates the
 *           number of factors for the given number (also provided in the task
 *           structure).
 *
 * @param    arg is a pointer to struct fact_task; describes the factorisation
 *           task.
 * @return   NULL. The number of factors for the given number in the range
 *           provided is set in the result member of struct fact_task.
 */
void *fact_worker(void *arg) {
  struct fact_task *const task = arg;
  task->result = 0;
  for (uint64_t i = task->from; i < task->to; i++) {
    if (task->num % i == 0) {
      task->result++;
    }
  }
  return NULL;
}

/**
 * @brief    Calculate the number of factors of the given number.
 *
 * @details  This function manages the threads used to calculate the number of
 *           factors of the given number. It creates and launches the threads,
 *           and collects the results when they have finished.
 *
 * @param    num is the number for which to calculate the number of factors.
 *           threads_count is the number of threads to use for the calculation.
 * @return   Number of factors of num.
 */
uint64_t factors_mp(uint64_t num, size_t threads_count) {
  /* Allocate factorisation tasks structure */
  struct fact_task *tasks = malloc(threads_count * sizeof(*tasks));
  /* Allocate array of worker thread pointers */
  pthread_t *threads = malloc(threads_count * sizeof(*threads));

  uint64_t start = 1;                /* range interval start */
  size_t step = num / threads_count; /* range interval step size */

  /* Initialise the factorisation tasks array */
  for (size_t i = 0; i < threads_count; i++) {
    tasks[i].num = num;
    tasks[i].from = start;
    tasks[i].to = start + step;
    start += step;
  }
  tasks[threads_count - 1].to = num + 1;

  /* Create and start worker threads to calculate factors in each range */
  for (size_t i = 0; i < threads_count; i++) {
    pthread_create(threads + i, NULL, fact_worker, tasks + i);
  }

  uint64_t result = 0; /* number of factors for given number */
  /* Sum results from all threads */
  for (size_t i = 0; i < threads_count; i++) {
    pthread_join(threads[i], NULL);
    result += tasks[i].result;
  }

  free(tasks);
  free(threads);
  return result;
}

int main(void) {
  uint64_t input = 2000000000;
  printf("Factors of %" PRIu64 ": %" PRIu64 "\n", input,
         factors_mp(input, THREADS));
  return 0;
}
