#include <omp.h>
#include <stdio.h>

#define N 100000
int main() {
  int tab[N];
  int sum  = 0;
  for (int i =0; i < N; i++) 
    tab[i] = i;
  
  #pragma omp parallel num_threads(2)
  {
    #pragma omp for reduction(+:sum)
    for(int i = 0; i < N; i++)
      sum += tab[i];
  }
  printf("%d\n", sum);
}