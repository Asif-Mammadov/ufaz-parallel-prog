#include <stdio.h>
#include <omp.h>
int main() {
double t_ref,t_end;
#pragma omp parallel
{
    t_ref= omp_get_wtime();
	#pragma omp for
	for(int i=0;i<1000000;i++)
		for(int j=0;j<10000;j++);//delay
    t_end= omp_get_wtime();
}
    printf("Execution time=%lf\n", (t_end-t_ref));
    return 0;
}