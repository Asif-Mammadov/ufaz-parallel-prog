#include <stdio.h>
#include <omp.h>
int main() {
  #pragma omp parallel
  {
    #pragma omp single
    { 
      #pragma omp task
      printf("Hello,\n");
      #pragma omp task
      printf("world!\n");
    }  
  }
  return 0;
}