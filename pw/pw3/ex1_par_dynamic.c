#include <stdio.h>
#include <omp.h>

#define N 500
int main()
{
  double C[N][N], A[N][N], B[N][N], start_time, end_time;
  size_t i, j, k;
  #pragma omp parallel
  {
  start_time = omp_get_wtime();
  #pragma omp for collapse(3) schedule(dynamic)
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      for (k = 0; k < N; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  }
  end_time = omp_get_wtime();
  printf("Exection time : %lf\n", end_time - start_time);
}