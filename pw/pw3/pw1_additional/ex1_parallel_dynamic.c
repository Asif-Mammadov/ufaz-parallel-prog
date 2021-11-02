#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#define N 1000
int main()
{
  size_t i, j, k;
  double start_time, end_time;
  double **C, **A, **B;
  A = (double**)malloc(N * sizeof(double*));
  B = (double**)malloc(N * sizeof(double*));
  C = (double**)malloc(N * sizeof(double*));

  for (i = 0; i < N; i++) {
    A[i] = (double*)malloc(N * sizeof(double));
    B[i] = (double*)malloc(N * sizeof(double));
    C[i] = (double*)malloc(N * sizeof(double));
  }

  // initialize A and B
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = 2 * (i + j);
    }
  }

  start_time = omp_get_wtime(); 
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      C[i][j] = 0.;
      for (k = 0; k < N; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  end_time = omp_get_wtime();
  printf("Execution time : %lf\n", end_time - start_time);

  // Free the memory
  for (i = 0; i < N; i++){
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }
  free(A);
  free(B);
  free(C);
}