#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int fibo(int n) {
  if (n < 2)
    return n;
 
  int i,j;	
  #pragma omp task shared(i) 
  i=fibo(n-1);
  #pragma omp task shared(j) 
  j=fibo(n-2);
  #pragma omp taskwait
  return i + j;
 
}

int main(int argc, char* argv[]) {
  double t_ref,t_end;
  int n = atoi(argv[1]);
  omp_set_dynamic(0);
  omp_set_num_threads(4);
  #pragma omp parallel 
  {
    #pragma omp single
	{
	 t_ref= omp_get_wtime();
     printf("fibo(%d) = %d\n", n , fibo(n));
     t_end= omp_get_wtime();
     printf("Execution time=%lf\n", (t_end-t_ref));
	}
  }
  return 0;
}