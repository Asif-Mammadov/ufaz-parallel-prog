#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
	int tid;
	#pragma omp parallel private(tid) num_threads(2)
	{
	tid=omp_get_thread_num();	
	printf("Start thread num%d\n",tid);
	#pragma omp sections nowait
	{
	#pragma omp section
		{
			for(int i=0;i<5;i++){
					for(int j = 0; j < 10000; j++);
				printf("Thread num %d i=%d\n",tid,i);
			}
		}
	#pragma omp section	
		{
		    for(int i=0;i<10;i++){
			    printf("Thread num %d i=%d\n",tid,i);			
				}
		}
	}	
	#pragma omp barrier
	printf("End thread num%d\n",tid);
	}
}

