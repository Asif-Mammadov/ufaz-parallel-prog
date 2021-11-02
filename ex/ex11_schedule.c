#include <stdio.h>
#include <omp.h>
int main() {
int i, tid;
#pragma omp parallel private(tid) 
{
tid = omp_get_thread_num();
if(tid == 2)
   for (int i = 0; i < 100000000;  i++);
#pragma omp for schedule(auto) //schedule(dynamic, 3)
for (i = 0; i < 8; i++)
   printf("Thread nb %d execute index=%d \n",tid,i );
}
return 0;
}