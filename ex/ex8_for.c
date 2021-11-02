#include <omp.h>
#include <stdio.h>

int main() {
  int i, tid;
#pragma omp parallel private(tid) num_threads(3)
  {
    tid = omp_get_thread_num();
#pragma omp for
    for (i = 0; i < 8; i++)
      printf("Thread nb %d execute index=%d \n", tid, i);
  }
  return 0;
}
