#include<stdio.h>
#include<omp.h>

#define SIZE 5

int get_rank(int n, int *a, int size) {
  int c = 0;
  for (int i = 0; i < size; i++) {
    if (n > a[i])
      c++;
  }
  return c;
}

void rank_sort(int *a, int *b, int size) {
  int index;
  #pragma omp parallel for private(index)
  for (int i = 0; i < 5; i++) {
    index = get_rank(a[i], a, SIZE); 
    b[index] = a[i];
  }
}

int main() {
  int a[SIZE] = {3,6,12,2,14};
  int b[SIZE];
  rank_sort(a, b, SIZE);
  for(int i = 0; i < SIZE; i++) 
    printf("%d ", b[i]);
  printf("\n");
  return 0;
}