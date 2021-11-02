#include <stdio.h>
#include <omp.h>
int main()
{
int tid;
float a;
#pragma omp parallel private(a,tid)
{
a = 1000.;
#pragma omp master)
{
a = -1000.;
}
tid=omp_get_thread_num();
printf("Thread id : %d ; a =%f\n",tid,a);
}
return 0;
}