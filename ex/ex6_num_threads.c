#include <stdio.h>
#include <omp.h>
int main() {
  #pragma omp parallel num_threads(3)
  {
   int status=omp_in_parallel(); 
    printf("Program is executed in parallel(%d)\n", status);
  }
  return 0;
}