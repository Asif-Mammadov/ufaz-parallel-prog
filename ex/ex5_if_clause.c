#include <stdio.h>
#include <omp.h>
#define n 5
int main() {
  #pragma omp parallel if(n>=100)
  {
   int status=omp_in_parallel(); 
    printf("Program is executed in parallel(%d)\n", status);
  }
  return 0;
}