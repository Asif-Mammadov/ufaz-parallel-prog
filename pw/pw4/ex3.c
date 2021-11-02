#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
  int p;
#pragma omp parallel sections default(shared)
  {
#pragma omp section
    {
      p = omp_get_thread_num();
      printf("Th%d: Hello\n", p);
    }
#pragma omp section
    {
      p = omp_get_thread_num();
      printf("Th%d: World\n", p);
    }
#pragma omp section
    {
      p = omp_get_thread_num();
      printf("Th%d: Bye\n", p);
    }
  }
  return 0;
}