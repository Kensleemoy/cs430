#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PERFORMANCE 0

int main(int argc, char *argv[]) {
    int input;
    char* next;
    double upperBound, result, sign;

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0')) {
            upperBound = input;
            result = 0.0;
            sign = 1.0;
            
#if (PERFORMANCE == 1)
            
            struct timeval* timerInitial = (struct timeval*) malloc(sizeof(struct timeval));
            gettimeofday(timerInitial,NULL);
            time_t secondsInitial = timerInitial->tv_sec;
            suseconds_t microSecInitial = timerInitial->tv_usec;
            unsigned long initialInMicro = secondsInitial * 1000000 + microSecInitial;
            struct timeval* timerFinal   = (struct timeval*) malloc(sizeof(struct timeval));
            
#endif
            int i;
            for(i=0; i<=upperBound; i++) {
                result += sign/(2.0*((double)i)+1.0);
                sign = -sign;
            }
            result = 4*result;
            
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
            
            fprintf(f, "Leibniz, Single-Threaded (msec) == %lu\n", (finalInMicro-initialInMicro));
            fclose(f);
            
#endif
            printf("%lf\n", result);
            return 0;
        } else {
            printf("USAGE: ./piLeib <integer>\n");
            return -1;
        }
    } else {
        printf("USAGE: ./piLeib <integer>\n");
        return -1;
    }
}
