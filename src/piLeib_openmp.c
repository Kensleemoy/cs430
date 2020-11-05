#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define PERFORMANCE 1

int main(int argc, char *argv[]) {
    
    // TH: experimental.
    long input;
    
    char* next;
    
    // TH: experimental.
    long upperBound, i;
    double result, sign;
    
    // TH: holds on to partial contribution per thread.
//  double partial_each;
    double partial_per_thread;
    
    // TH: holds on to thread id.
    int tid;
    
    // TH: holds on to loop contribution per thread.
//  long loop_cnt;
    
    // TH: https://computing.llnl.gov/tutorials/openMP/samples/C/omp_getEnvInfo.c
    // TH: retrieves maximum number of threads available.
    int maxt = omp_get_max_threads();
//  printf("[main]: max threads == %d.\n",maxt);
    
    // TH: represents chunk size.
    long chunk;
    
    // TH: represents left-over.
    long remainder;
    
    if (!(argc == 2)) {
       printf("USAGE: ./piLeib <integer>\n");
       return -1;
    }
    
    // TH: validates input count.
    {
        
        // TH: converts string to long.
        input = strtol(argv[1], &next, 10);
        
        // TH: validates input, again.
        if (!((next != argv[1]) && (*next == '\0'))) {
           printf("USAGE: ./piLeib <integer>\n");
           return -1;
        }
        
        {
            
            // TH: initializes upper bound.
            upperBound = input;
            
            // TH: updates chunk size.
            chunk = (upperBound>maxt)?upperBound/maxt:maxt/upperBound;
//          printf("[main]: chunk == %lu.\n",chunk);
            
            // TH: updates remainder.
            remainder = (upperBound>maxt)?upperBound%maxt:0;
            
            // TH: initializes global 'result' among all threads.
            result  = 0.0;
            sign    = 1.0;
            
#if (PERFORMANCE == 1)
            
            struct timeval* timerInitial = (struct timeval*) malloc(sizeof(struct timeval));
            gettimeofday(timerInitial,NULL);
            time_t secondsInitial = timerInitial->tv_sec;
            suseconds_t microSecInitial = timerInitial->tv_usec;
            unsigned long initialInMicro = secondsInitial * 1000000 + microSecInitial;
            struct timeval* timerFinal   = (struct timeval*) malloc(sizeof(struct timeval));
            
#endif
            
            // TH: https://computing.llnl.gov/tutorials/openMP/samples/C/omp_dotprod_openmp.c
            // TH: invokes parallel threads.
            #pragma omp parallel shared(upperBound,result,chunk,remainder) private(tid, /*partial_each,*/ partial_per_thread, sign/*, loop_cnt*/) num_threads(maxt)
            {
               
               // TH: retrieves OpenMP thread id.
               tid = omp_get_thread_num();
               
               // TH: initializes OpenMP variables per thread.
//             partial_each       = 0.0;
               partial_per_thread = 0.0;
               
               sign     = 1.0;
//             loop_cnt = 0.0;
               
               // TH: computes partial sum per thread.
               long start_ = (long) (tid*chunk);
               long end_   = (long) (tid*chunk+chunk);
               
               if(upperBound>maxt && tid==maxt-1) end_ += remainder;
               
               for(i=start_; i<end_; i++) {
                  
                  // TH: if other threads already handled work load (i.e. more threads than bounds).
                  if(start_>=upperBound) break;
                  
                  partial_per_thread  += (sign/((2.0)*((double)i)+1.0));
//                loop_cnt = i-start_;
                  sign    = (-1) * sign;
                  
               }//for i.
               
               // TH: computes total sum among threads (i.e.per process).
               #pragma omp for reduction(+:result)
               for(i=0; i<maxt; i++)
                  result += (4.0) * partial_per_thread;
               
//             printf("[main]: Thread %d contributed %lu loops.\n",tid,loop_cnt);
//             printf("[main]: Thread %d contributed %f.\n",tid,partial_per_thread);
               
            }//pragma.
            
#if (PERFORMANCE == 1)
            
            gettimeofday(timerFinal,NULL);
            time_t secondsFinal = timerFinal->tv_sec;
            suseconds_t microSecFinal= timerFinal->tv_usec;
            unsigned long finalInMicro = secondsFinal* 1000000 + microSecFinal;
            
            const char *log_perf  = "log_leibniz_perf.txt";
            FILE *f = NULL;
            if ((f = fopen(log_perf, "a")) == NULL) {
               const char * log_error = "log_mmio_error.txt";
               FILE * log_file = fopen (log_error , "a");
               fprintf(log_file, "Usage: %s could NOT be written.\n", log_perf);
               fclose (log_file);
               return 1;
            }//if NULL.
            
            fprintf(f, "Leibniz, Multi-Threaded (msec)  == %lu\n", (finalInMicro-initialInMicro));
            fclose(f);
            
#endif
            
            printf("%lf\n", result);
            return 0;
            
        }
        
    }
    
}

