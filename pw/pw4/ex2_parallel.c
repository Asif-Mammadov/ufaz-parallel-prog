#include <stdio.h>
#include <omp.h>
#include<stdbool.h>

#define PRIME_MAX 500000
#define PRIME_MIN 3
#define N 100000

int main()
{
  size_t primes[N], nb_primes = 0;
  size_t divisor;
  bool is_prime;
  double start_time, end_time;

  start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for private(is_prime, divisor) 
    for (size_t i = PRIME_MIN; i < PRIME_MAX; i += 2)
    {
      is_prime = true;
      divisor = PRIME_MIN;
      while ((divisor < i) && is_prime)
      {
        if ((i % divisor) == 0)
          is_prime = false;
        divisor += 2;
      }
      if (is_prime)
      {
        primes[nb_primes] = i;
        #pragma omp atomic
        nb_primes++;
      }
    }
  }
  end_time = omp_get_wtime();
  printf("Nb primes=%zu\nExecution time : %lf\n", nb_primes, end_time - start_time);
}