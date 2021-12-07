#include<stdio.h>
#include<omp.h>

int main() {
  int sum = 0;
  int n = 0;
  int a[1000];
  for (int i = 0; i < 1000; i++) {
    a[i] = i + 1;
  }
  #pragma omp parallel 
  {
    #pragma omp for reduction (+:sum)
    for (int i = 0; i < 1000; i++) {
      if (a[i] % 5 == 0)
        sum++;
    }
  }
  printf("Occurence of 6 : %d\n", sum);
}