#include <stdio.h>
#include <omp.h>
int main()
{
    int i,sum = 0; 
    #pragma omp parallel shared(sum) 
    {       
        #pragma omp for reduction(+:sum) nowait
        for (i = 0; i < 1000; i++) {
               sum = sum + i;
            }
        // #pragma omp barrier (to synchronize between all threads)
		printf("%d\n", sum); // sum is indeterminate here
    }          
    return 0;
}
