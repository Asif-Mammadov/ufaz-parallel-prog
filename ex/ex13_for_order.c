#include <stdio.h>
#include <omp.h>
int main() {
int i, tid;
#pragma omp parallel private(tid) num_threads(2)
{
tid = omp_get_thread_num();
#pragma omp for ordered
for (i = 0; i < 4; i++)
{
   #pragma omp ordered
   printf("Thread nb %d execute index=%d \n",tid,i );
}
}
return 0;
}
