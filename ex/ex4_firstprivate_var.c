#include <stdio.h>
#include <omp.h>
int main()
{
float a = 100.;
#pragma omp parallel firstprivate(a)
{
int tid = omp_get_thread_num();
a = a + tid;
printf("thread %d, a = %1f\n",tid,a);
}
printf("out of parallel region a=%1f\n",a);
return 0;
}