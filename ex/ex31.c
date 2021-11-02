#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  omp_lock_t lock;
  omp_init_lock(&lock);
  omp_set_lock(&lock);
#pragma omp parallel
  {
#pragma omp sections
    {
#pragma omp section
      {
        printf("Hello\n");
        omp_unset_lock(&lock);
        omp_unset_lock(&lock);
      }
#pragma omp section
      {
        omp_set_lock(&lock);
        printf("World\n");
        omp_unset_lock(&lock);
      }
    }
  }
  omp_destroy_lock(&lock);
}