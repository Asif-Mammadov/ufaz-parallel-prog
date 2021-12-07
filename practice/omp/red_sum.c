#include<stdio.h>
#include<omp.h>

int main() {
  int tid, sum;
  int a[100];
  for (int i = 0; i < 100; i++) {
    a[i] = i;
  }
  #pragma omp parallel 
  {
    #pragma omp for reduction(+:sum)
    for (int i = 0; i < 100; i++) {
      sum += a[i];
    } 
  }
  printf("%d\n", sum);
}