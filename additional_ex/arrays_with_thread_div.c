#include <omp.h>
#include <stdio.h>

#define N 10000
int main() {
  int a[N];
  for (int i = 0; i < N; i++) {
    a[i] = i;
  }
  int tid;
  long sum = 0;
  double time_start, time_end;
#pragma omp parallel num_threads(2)
  {
    time_start = omp_get_wtime();
    int tid = omp_get_thread_num();
    if (tid == 0) {
      for (int i = 0; i < N / 2; i++) {
        for (int k = 0; k < 100000; k++) {
#pragma omp atomic
          sum += a[i];
        } // delay
      }
    } else {
      for (int i = N / 2; i < N; i++) {
        for (int k = 0; k < 100000; k++) {
#pragma omp atomic
          sum += a[i];
        } // delay
      }
    }
  }

  time_end = omp_get_wtime();
  printf("Sum is %ld\nTime : %lf\n", sum, time_end - time_start);
}