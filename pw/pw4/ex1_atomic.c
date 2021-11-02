#include<stdlib.h>
#include<stdio.h>
int main()
{
  size_t nb_threads = 0;
  #pragma omp parallel
  {
    #pragma omp atomic
    nb_threads++;
  }
  printf("nb_threads = %zu\n", nb_threads);
}