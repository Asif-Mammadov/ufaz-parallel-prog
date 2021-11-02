#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define n 500000
int main()
{
  int i,time1,time2,tab [n];
  double s=0;
  for(i=0;i<n;i++)
	tab[i]=i;
  time1=omp_get_wtime();  
  #pragma omp parallel for private(i) reduction(+:s)
  for(i=0;i<n;i++)
  { 
	s=s+tab[i];	
  }	
  time2=omp_get_wtime();
  printf("Sum=%f execution time=%d\n",s,(time2-time1));
  return 0;
}
