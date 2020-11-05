#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>

//Declaring function prototypes
long fib(long n);

int main(int argc, char *argv[]) {
    int input;
    char* next;
    // long term;
    // long result = 0;
    clock_t start, end;
    // double time;         //this will be used for timing for the report
    long term;
    long firstT = 0;
    long secondT = 1;
    long nextTerm = 0;
    long result = 0;

    //Ensuring the correct number of arguments are there
    if (argc == 2) {

        //Grabbing input
        input = strtol(argv[1], &next, 10);

        //Error handling to ensure valid input
        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = (long)input;

            //Start timer
            start = clock();

            //Iterative fibonacci calculation
            #pragma omp parallel for shared(term, result, firstT, secondT, nextTerm)
            for(int i = 0; i <= term; i++) {
                if ((long)i == term) {
                    result = firstT;
                }
                nextTerm = firstT + secondT;
                firstT = secondT;
                secondT = nextTerm;
            }

            //Stop timer
            end = clock();

            //calculate time
            // time = ((double)(end - start)) / (double)CLOCKS_PER_SEC;

            //print results
            //Time is commented out for use later
            // printf("Time: %f\n", time);
            printf("The [%ld] number in the Fibonacci sequence: %ld\n", term, result);
            return 0;

        } else {
            printf("USAGE: ./fibonacci <natural integer number>\n");
            return -1;
        }
    } else {
        printf("USAGE: ./fibonacci <natural integer number>\n");
        return -1;
    }
}