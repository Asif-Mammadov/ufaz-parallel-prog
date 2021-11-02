#include <omp.h>
#include <stdio.h>
int main() {
  float a = 100.;
#pragma omp parallel private(a) 
  {
    int tid = omp_get_thread_num();
    a = a + tid;
    printf("thread %d, a = %1f\n", tid, a);
  }
  printf("out of parallel region a=%1f\n", a);
  return 0;
}