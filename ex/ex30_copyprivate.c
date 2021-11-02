#include <stdio.h>
#include <omp.h>

int main() {
int tid;
float a;
#pragma omp parallel private(a)
{
a = 10000;
#pragma omp single copyprivate(a)
{
	a = -10000;
}
tid = omp_get_thread_num ();
printf("Thread id :%d a =%f\n",tid,a);
}
  return 0;
}