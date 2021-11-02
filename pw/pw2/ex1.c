#include<stdio.h>
#include<omp.h>
int main() {
#pragma omp parallel num_threads(2)
printf("Hello\n");
printf("World\n");
return 0;
}