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
      printf("Bye\n");
    }  
  }
  
  return 0;
}