#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
  int p;
  omp_lock_t lock1, lock2;
  omp_init_lock(&lock1);
  omp_init_lock(&lock2);
  omp_set_lock(&lock1);
  omp_set_lock(&lock2);
#pragma omp parallel sections default(shared)
  {
#pragma omp section
    {
      p = omp_get_thread_num();
      printf("Th%d: Hello\n", p);
      omp_unset_lock(&lock1);
    }
#pragma omp section
    {
      omp_set_lock(&lock1);
      p = omp_get_thread_num();
      printf("Th%d: World\n", p);
      omp_unset_lock(&lock2);
      omp_unset_lock(&lock1);
    }
#pragma omp section
    {
      omp_set_lock(&lock2);
      p = omp_get_thread_num();
      printf("Th%d: Bye\n", p);
      omp_unset_lock(&lock2);
    }
  }
  omp_destroy_lock(&lock1);
  omp_destroy_lock(&lock2);
  return 0;
}