#include <stdio.h>
#include <omp.h>

int main () {
  int x = 2;
  printf("start id =%d, x=%d\n", omp_get_thread_num(), x);
  x = x + 2;
  #pragma omp parallel num_threads(2)
  {
    int y = 3;
    printf("Hello id=%d, x=%d, y=%d\n", omp_get_thread_num(), x, y);
  }
  return 0;
}