#include <stdio.h>
#include <omp.h>

#define N 10000
int main () {
  int a[N];
  for (int i = 0; i < N; i ++) {
    a[i] = i;
  }

  int sum = 0;
  #pragma omp parallel num_threads(2)
  {
    #pragma omp for
    for (int i = 0; i < N; i++) {
      #pragma omp atomic
      sum += a[i];
      printf("id=%d, sum = %d\n", omp_get_thread_num(), sum);
  }
  printf("Result %d\n", sum);
}
}