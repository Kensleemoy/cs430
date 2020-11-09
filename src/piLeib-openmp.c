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
    
    double pi = 1.0;

    int i = 3;
    int j = 0;
    
#if (PERFORMANCE == 1)
            
            /*
            struct timeval* timerInitial = (struct timeval*) malloc(sizeof(struct timeval));
            gettimeofday(timerInitial,NULL);
            time_t secondsInitial = timerInitial->tv_sec;
            suseconds_t microSecInitial = timerInitial->tv_usec;
            unsigned long initialInMicro = secondsInitial * 1000000 + microSecInitial;
            struct timeval* timerFinal   = (struct timeval*) malloc(sizeof(struct timeval));
            */
            
            // TH: retrieves maximum number of threads available.
            int num_threads_ = omp_get_max_threads();
            
            double start;
            double end;
            start = omp_get_wtime();
            
#endif
    
#if (PERFORMANCE == 1)
    int thread_count_;
    for (thread_count_=1; thread_count_ <= num_threads_; thread_count_++) {
       pi = 1.0;
       #pragma omp parallel for private(i, j) reduction(+:pi) num_threads(thread_count_)
#else
       #pragma omp parallel for private(i, j) reduction(+:pi)
#endif
       
       for(i=3; i <= n; i++) {
           if(i%2 == 1) {
               if(j%2 == 0) {
                   pi = pi - (1.0/(double)i);
                   j++;
               } else {
                   pi = pi + (1.0/(double)i);
                   j++;
               }
           }
       }
       pi = pi*4;
       
#if (PERFORMANCE == 1)
            
            end = omp_get_wtime();
            
            /*
            gettimeofday(timerFinal,NULL);
            time_t secondsFinal = timerFinal->tv_sec;
            suseconds_t microSecFinal= timerFinal->tv_usec;
            unsigned long finalInMicro = secondsFinal* 1000000 + microSecFinal;
            */
            
            const char *log_perf  = "./output/log_leibniz_perf_openmp.txt";
            FILE *f = NULL;
            if ((f = fopen(log_perf, "a")) == NULL) {
               const char * log_error = "log_mmio_error.txt";
               FILE * log_file = fopen (log_error , "a");
               fprintf(log_file, "Usage: %s could NOT be written.\n", log_perf);
               fclose (log_file);
               return 1;
            }//if NULL.
            
//          fprintf(f, "Leibniz, Multi-Threaded (msec)  == %lu\n", (finalInMicro-initialInMicro));
            
            fprintf(f, "Leibniz, Multi-Threaded (sec, thread_count_:%d, n:%d)  == %f\n", thread_count_, n, (end - start));
            fclose(f);
            
    }//for thread_count_.
#else
    printf("%1.6f",pi);
#endif
    
    return 0;
    
}

