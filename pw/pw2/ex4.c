#include <stdio.h>
#include <omp.h>

#define SIZE 10000
int main()
{
  int a[SIZE];
  int sum = 0;
  for (int i = 0; i < SIZE; i++)
    a[i] = i;

  #pragma omp parallel
  {
    #pragma omp for reduction(+:sum)
    for (int i = 0; i < SIZE; i++)
      sum += i;
  }
  printf("Average : %f\n", 1.0 * sum / SIZE);
  return 0;
}