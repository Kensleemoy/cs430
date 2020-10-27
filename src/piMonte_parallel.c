#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

//To set number of threads beforehand, use env var
//export OMP_NUM_THREADS=4
int main(int argc, char **argv) {
	int drops = 0;
	if (argc == 2) {
		drops = atoi(argv[1]);
		if(!(drops > 0) ) {
			printf("%s\n", "argument must be greater than zero");
			exit(-1);
		}
	} else {
		printf("this requires one argument\n");
		exit(-1);
	}

	double sum = 0.0;
	double x = 0.0;
	double y = 0.0;
	int i;
	srand(3141592653);
	
	#pragma omp parallel for private(x, y) reduction(+:sum) 
	for (i=0; i < drops; i++) {
		x = rand()%(10000+1);
		y = rand()%(10000+1);
		if ( (x*x)+(y*y) <= (10000*10000) ) {
			sum += 1;
		}
	}

	double pi = (4.0 * sum) / drops;
	printf("%f\n", pi);
	return 0;

//	#pragma omp parallel
//	{
//	printf("This will print a lot\n");
//	int rank = omp_get_thread_num();
//	int n = omp_get_max_threads();
//        printf("Core #%d out of %d says hello world\n", rank, n);
//	}
//	printf("This should print only once\n");
}
