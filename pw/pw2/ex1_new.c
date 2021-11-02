#include <stdio.h>
#include <omp.h>

int main()
{
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    printf("---Thread %d\n", tid);
    printf("Hello\n");
    printf("World\n");
  }
  return 0;
}