#include <omp.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  printf("Start id=%d\n", omp_get_thread_num());
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int size = omp_get_num_threads();
    printf("I'm thread %d in a thread team of size %d\n", tid, size);
  }
  printf("End id=%d\n", omp_get_thread_num());
  return 0;
}