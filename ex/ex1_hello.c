#include <stdio.h>
#include <omp.h>

int main() {
  int b = 3;
  #pragma omp parallel num_threads(b)
  {
    int tid = omp_get_thread_num();
    int size = omp_get_num_threads();
    if(tid==0)
    printf("I'm thread number 0 in a thread team of size %d\n", size);
    else
    printf("I'm thread %d in a thread team of size %d\n", tid, size);
  }
  return 0;
}