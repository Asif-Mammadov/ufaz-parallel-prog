#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void hello(){printf("Hello thread:%d\n",omp_get_thread_num());}
void world(){printf("World thread:%d\n",omp_get_thread_num());}
int main()
{	
	#pragma omp parallel 
	{
	#pragma omp sections nowait
	{
	#pragma omp section
		hello();
	#pragma omp section	
		world();
	}
	}

}
