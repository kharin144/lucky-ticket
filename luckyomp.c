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
	
	//debug
	//printf("%s\n", argv[1]);
	//printf("Treads: %d\n", omp_get_num_threads() );

	char *str;
	str = (char*) malloc( sizeof(char)*strlen(argv[1]) );
	strcpy(str,argv[1]);

	for(int i=0;i< strlen(argv[1]); i++){
		if( (!isdigit(str[i])) && (str[i]!='d') )
			exit(2);
	}

	int *mass;
	//int *digits;
	//int tmp, j;
	//int sum = 0;
	int threads;
	const int half = strlen(str)/2;//amount of digits
	const int limit= 9 * half; //maximum sum in part
	
	free(str);
	
	mass   = (int*) malloc( sizeof(int) * (limit+1) );
	for( int i=0; i<=(limit+1); i++ )
			mass[i]=0;



//	#pragma omp parallel firstprivate(sum, digits) private(j,tmp) shared(mass,threads)
	#pragma omp parallel shared(mass, threads)
	{
		const int tnum=omp_get_thread_num();
		//threads= omp_get_num_threads();
		
		int *lmass;
		lmass   = (int*) malloc( sizeof(int) * (limit+1) );
		#pragma omp single
		{
			threads= omp_get_num_threads();
	
		}// end of single section
		
		#pragma omp barrier
		// initialisation
		for( int i=0; i<=(limit+1); i++ )
			lmass[i]=0;
		
		int sum=0, tmp;
		// heaviest part of calculating
		
		const int power = pow(10, half);
		#pragma omp for
		for ( int i=0; i< power; i++ ){
			tmp=i;
	
			for (int j=0; j<half; j++){
				sum+=tmp%10;
				tmp/=10;
			}
			
			lmass[sum]++;
			sum=0;
		}
		
		for(int i=0; i<limit+1; i++)
			mass[i]+=lmass[i];
			
		free(lmass);

	}//end of parallel section

	//debug
	//for(int i=0; i<=(limit+1)*threads; i++) printf("%d ", mass[i]); printf("\n");
	
	for(int i=0; i<limit+1; i++)
		printf("%d ", mass[i]);
	
	printf("\n");
	
	//time
	//printf("%f\n", clock()/(CLOCKS_PER_SEC + 0.) );

	free(mass);

}
