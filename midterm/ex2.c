#include<stdio.h>
#include<omp.h>

#define SIZE 8

// counts even numbers if isEven is true (!=0), 
// and odd numbers if isEven is false (=0)
int count(int *a, int size, int isEven) {
  int val = (isEven) ? 0 : 1; 
  int c = 0;
  #pragma omp parallel for reduction (+: c)
  for (int i = 0; i < SIZE; i++) {
    if (a[i] % 2 == val)
      c++;
  }
  return c;
}

int main() {
  int a[SIZE] = {1, 3, 4, 6, 7, 8, 9, 121};
  printf("Count even: %d\nCount odd: %d\n", count(a, SIZE, 1), count(a, SIZE, 0));
  return 0;
}