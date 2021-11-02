#include <stdio.h>
#include <omp.h>
int main() {

  #pragma omp parallel
  {
    #pragma omp single
    { 
      printf("Hello,\n");
      printf("world!\n");
    }  
  }
  
  return 0;
}