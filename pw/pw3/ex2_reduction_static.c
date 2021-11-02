#include <stdio.h>
#include <omp.h>
int main()
{
  size_t nb_steps = 100000000;
  double pi, term, start_time, end_time;
  double sum = 0.;
  double step = 1. / (double)nb_steps;
  start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for private(term) reduction(+:sum)
    for (size_t i = 0; i < nb_steps; i++)
    {
      // for(int j = 0; j < 20; j++); // for delay to see difference
      term = (i + 0.5) * step;
      sum += 4. / (1. + term * term);
    }
  }
  pi = step * sum;
  end_time = omp_get_wtime();
  printf("PI = %f\nExecution : %f\n", pi, end_time - start_time);
}