#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibo(int n) {
  if (n < 2)
    return n;

  return fibo(n-1) + fibo(n-2);
}

int main(int argc, char* argv[]) {
  double t_ref,t_end;
  int n = atoi(argv[1]);
  t_ref= omp_get_wtime();
  printf("fibo(%d) = %d\n", n , fibo(n));
  t_end= omp_get_wtime();
  printf("Execution time=%lf\n", (t_end-t_ref));
  return 0;
}