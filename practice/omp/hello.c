#include<stdio.h>
#include<omp.h>

int main() {
  #pragma omp parallel num_threads(4)
  {
    int tid = omp_get_thread_num();
    int size = omp_get_num_threads();
    printf("I am thread %d out of %d\n", tid, size);
  }
}