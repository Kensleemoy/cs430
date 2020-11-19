#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>

#define PERFORMANCE 1

int main(int argc, char *argv[]) {
    if(argc != 2) {
        return -1;
    }

    int n = atoi(argv[1]);
    if(strncmp(argv[1], "0", 1) != 0 && n==0) {
        return -1;
    } 
    if(n<0) {
        fprintf(stderr, "index must be be greater than or equal to 0\n");
        return -1;
    }
    
    int i=0;
    
    double pi = 0.0;
    
#if (PERFORMANCE == 1)
    
    double start;
    double end;
    
//  // TH: measures overall performance, default total thread count.
//  if(1) {
//     // TH: starts timer.
//     start = omp_get_wtime();
//     #pragma omp parallel for private(i) reduction(+:pi)
    
    // TH: https://computing.llnl.gov/tutorials/openMP/samples/C/omp_getEnvInfo.c
    // TH: measures specific performance, per given thread count.
    int maxt = omp_get_max_threads();
    int thread_count_;
    for (thread_count_=1; thread_count_ <= maxt; thread_count_++) {
       // TH: starts timer.
       start = omp_get_wtime();
       #pragma omp parallel for private(i) reduction(+:pi) num_threads(thread_count_)
    
#else
       // TH: runs normally.
       #pragma omp parallel for private(i) reduction(+:pi)
#endif
       
       // TH: assigns each private loop index, per thread.
       // TH: https://computing.llnl.gov/tutorials/openMP/samples/C/omp_workshare1.c
       for(i = 0; i <= n; i++) {
          pi += (((i%2==0)?(1.00):(-1.00))/((2.0)*((double)i)+1.0));
       }//for i.
       
       // TH: retrieves overall result.
       pi = pi*4;
       
#if (PERFORMANCE == 1)
       
       // TH: ends timer.
       end = omp_get_wtime();
       
       const char *log_perf  = "./output/log_leibniz_perf_openmp.txt";
       FILE *f = NULL;
       if ((f = fopen(log_perf, "a")) == NULL) {
          const char * log_error = "log_mmio_error.txt";
          FILE * log_file = fopen (log_error , "a");
          fprintf(log_file, "Usage: %s could NOT be written.\n", log_perf);
          fclose (log_file);
          return 1;
       }//if NULL.
       
//     fprintf(f, "Leibniz, Multi-Threaded (sec, n:%d)  == %f\n", n, (end - start));
       fprintf(f, "Leibniz, Multi-Threaded (sec, thread_count_:%d, n:%d)  == %f\n", thread_count_, n, (end - start));
       
       fclose(f);
       
    }//for thread_count_.
#else
       printf("%1.6f",pi);
#endif
    
    return 0;
    
}

