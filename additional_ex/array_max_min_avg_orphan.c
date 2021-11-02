#include<stdio.h>
#include<omp.h>
#include <limits.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100

long min (long *a, int size) {
  long min = LONG_MAX;
  for (long i = 0; i < size; i++) {
    if (a[i] < min) 
      min = a[i];
  }
  return min;
}

long max (long *a, int size) {
  long max = LONG_MIN;
  for (long i = 0; i < size; i++) {
    if (a[i] > max)
      max = a[i];
  }
  return max;
}

double avg(long *a, int size) {
  long sum = 0;
  for (long i = 0; i < size; i++)
    sum += a[i];
  return (double) sum/size;
}

long * generate_arr(long size) {
  srand(time(0));
  long *a = (long*) malloc(size * sizeof(long));
  for (long i = 0; i < size; i++) {
    a[i] = rand() % 99999;
  }
  return a;
}
int main() {

  long *a = generate_arr(SIZE);
  double start, end;
  long max_v, min_v;
  double avg_v;
  start = omp_get_wtime();
  #pragma omp parallel 
  {
    #pragma omp sections nowait
    {
      #pragma omp section
      {
        min_v = min(a, SIZE);
        for (int i = 0; i < 10000; i ++)  //delay
          for(int j = 0; j <100000; j++);

        printf("Min: %ld\n", min_v);
      }
      #pragma omp section 
      {
        for (int i = 0; i < 100000; i ++) //delay
          for(int j = 0; j <10000; j++);
        max_v = max(a, SIZE);
        printf("Max: %ld\n", max_v);
      }
      #pragma omp section
      {
        avg_v = avg(a, SIZE);
        printf("Avg: %lf\n", avg_v);
      }
    }
  }
  end = omp_get_wtime();
  printf("Time : %lfs\n", end - start);
  free(a);
  return 0;
}