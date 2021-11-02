#include <stdio.h>
#include <omp.h>
int a;//static variable in c
void sub();
#pragma omp threadprivate (a)
int main()
{
a = 10000;
omp_set_dynamic(0);
#pragma omp parallel copyin(a)
{
	a = a + omp_get_thread_num ();
	sub();
}
printf("Out of parallel region, a=%d\n",a);
#pragma omp parallel
	printf("new parallel region,thread nb %d, a=%d\n",omp_get_thread_num(),a);
}
void sub(){
int b;
b = a + 200;
printf ("Thread nb %d ,b = %d\n",omp_get_thread_num(),b);
}