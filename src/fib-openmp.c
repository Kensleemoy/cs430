#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int input;
    char* next;
    long term;
    int firstT = 0;
    int secondT = 1;
    int nextTerm = 0;
    long result = 0;

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = (long)input;
            
            // for(int i = 0; i <= term; i++) {
            //     if (i == term) {
            //         result = firstT;
            //     }
            //     nextTerm = firstT + secondT;
            //     firstT = secondT;
            //     secondT = nextTerm;
            // }

            result = fib(term);

            printf("The [%d] number in the Fibonacci sequence: %ld\n", (int)term, result);
            return 0;
        } else {
            printf("USAGE: ./fibonacci <natural integer number>\n");
            return -1;
        }
    } else {
        printf("USAGE: ./fibonacci <natural integer number>= 0>\n");
        return -1;
    }
}

long fib(long n) {
    long i, j;
    if(n <= 1)
        return n;

    #pragma omp parallel task shared(i) if(n > 33)
    i = fib(n-1);

    #pragma omp parallel task shared(j) if(n > 33)
    j = fib(n-2);

    #pragma omp taskwait

    return i+j;
}