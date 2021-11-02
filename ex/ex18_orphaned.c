#include <stdio.h>
#include <omp.h>
#define SIZE 8
void init(int* vec) {
  size_t i;
  #pragma omp for
  for (i = 0; i < SIZE; i++)
  {
	printf("Thread nb %d execute i=%ld\n",omp_get_thread_num(),i);
    vec[i] = 0;
  }
}

int main() {
  int vec[SIZE];
  #pragma omp parallel
  init(vec);
  return 0;
}