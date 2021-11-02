#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int *a;
long fibo(long n) {
  printf("Here\n");
  if (n < 2)
    return n;
  if (a[n] != -1)
    return a[n];
  int i,j;
  #pragma omp task shared(i)
  {
    i=fibo(n-1);
    printf("i=%d\n", i);
  }
  #pragma omp task shared(j)
  {
    j=fibo(n-2);
    printf("j=%d\n", j);
  }
  #pragma omp taskwait
  a[n] = i + j;
  return i + j;
}

int main(int argc, char* argv[]) {
  double t_ref,t_end;
  int n = atoi(argv[1]);
  a = (int*) malloc((n+1) * sizeof(int));
  for (int i = 0; i < n + 1; i++) {
    a[i] = -1;
  }
  t_ref= omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    printf("fibo(%d) = %d\n", n , fibo(n));
  }
  t_end= omp_get_wtime();
  printf("Execution time=%lf\n", (t_end-t_ref));
  return 0;
}