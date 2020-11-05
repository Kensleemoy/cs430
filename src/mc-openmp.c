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
	unsigned int seed = 3141592653;
	srand(3141592653);
	
	#pragma omp parallel for private(x, y, seed) reduction(+:sum) 
	for (i=0; i < drops; i++) {
		x = rand_r(&seed)%(10000+1);
		y = rand_r(&seed)%(10000+1);
		if ( (x*x)+(y*y) <= (10000*10000) ) {
			sum += 1;
		}
	}

	double pi = (4.0 * sum) / drops;
	printf("%f\n", pi);
	return 0;
}
