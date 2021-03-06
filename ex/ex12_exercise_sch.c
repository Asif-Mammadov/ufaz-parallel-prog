#include <stdio.h>
#include <omp.h>
#define SIZE  100
#define CHUNK  10

int main() {
  int tid;
  double a[SIZE], b[SIZE], c[SIZE];
  
  for (int i = 0; i < SIZE; i++)
    a[i] = b[i] = i;

  #pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
      printf("Nb threads = %d\n", omp_get_num_threads());
    printf("Thread %d: starting...\n", tid);

    // Chunk size for dynamic if not specified is 1. It is better to always specify the chunk depending on the problem.
    #pragma omp for schedule(static, CHUNK)
    for (int i = 0; i < SIZE; i++) {
      c[i] = a[i] + b[i];
      printf("Thread %d: c[%d] = %g\n", tid, i, c[i]);
    }
  }
  return 0;
}