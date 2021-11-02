#include <stdio.h>
#include <omp.h>
#include <unistd.h>
int main() {
  int end = 0;
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      while (!end)
        printf("Not Done\n");
    }
    #pragma omp section
    {
      end = 1;
      sleep(10);
      printf("Done\n");
    }
  }
  return 0;
}