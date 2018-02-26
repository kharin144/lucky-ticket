#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]){

	if( argc<2 ) exit(1);
	
	printf("%s\n", argv[1]);

	char *str;
	str = (char*) malloc( sizeof(char)*strlen(argv[1]) );
	strcpy(str,argv[1]);

	for(int i=0;i< strlen(argv[1]); i++){
		if( (!isdigit(str[i])) && (str[i]!='$') )
			exit(2);
	}

	int *mass, *digits, tmp, j;
	int sum = 0, threads;
	const int half = strlen(str)/2;
	const int limit= 9 * half;

	mass   = (int*) malloc( sizeof(int) * (limit+1) );
	digits = (int*) malloc( sizeof(int) * half );


	for(int i=0; i<limit+1; i++)
		mass[i]=0;
	
	for(int i=0;i<half;i++)
		digits[i]=0;

	#pragma omp parallel firstprivate(sum, digits) private(j,tmp) shared(mass,threads)
	{

	int tnum=omp_get_thread_num();
	#pragma omp single
	{
		threads= omp_get_num_threads();
		mass   = (int*) malloc( sizeof(int) * (limit+1) * threads );
	}

	for( int i=tnum; i<(limit+1) * threads; i+=threads )
		mass[i]=0;

	for (int i=tnum; i< pow(10, half); i+=threads ){
		tmp=i;

		for (j=0; j<half; j++){
			sum+=tmp%10;
			tmp/=10;
		}
		
		mass[sum + (limit+1)*tnum]++; sum=0;
	}

	}//end of parallel section

	//debug
	//for(int i=0; i<(limit+1)*threads; i++) printf("%d ", mass[i]); printf("\n");

	for(int i=0;i<limit+1; i++)
	for(int j=1; j<threads;j++)
		mass[i]+=mass[(limit+1)*j+i];

	for(int i=0; i<limit+1; i++) printf("%d ", mass[i]);

	printf("\n%f", clock()/(CLOCKS_PER_SEC + 0.) );

	free(str);
	free(mass);free(digits);

}
