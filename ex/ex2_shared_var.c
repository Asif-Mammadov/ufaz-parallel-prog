#include <omp.h>
#include <stdio.h>
int main() {
  float a;
  a = 100;
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    a = a + 1;
    printf("thread %d, a = %f\n", tid, a);
  }
  printf("out of parallel region a=%f\n", a);
  return 0;
}