#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Declaring function prototypes
long fib(long n);

int main(int argc, char *argv[]) {
    int input;
    char* next;
    long term;
    long result = 0;

    //Ensuring the correct number of arguments are there
    if (argc == 2) {

        //Grabbing input
        input = strtol(argv[1], &next, 10);

        //Error handling to ensure valid input
        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = (long)input;

            //Starts Recursive call
            #pragma omp parallel shared(term, result) 
            {
                #pragma omp single 
                {
                    result = fib(term);
                }
            }
            printf("The [%d] number in the Fibonacci sequence: %ld\n", (int)term, result);
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

//Recursive function
long fib(long n) {
    long i, j;

    //Stop requirement --> stop creating new threads once n is a low enough value
    if(n <= 1)
        return n;

    //Term 1
    // #pragma omp task shared(i)
    // #pragma omp parallel task shared(i) if(n > 33)
    #pragma omp task shared(i) if(n > 33)
    i = fib(n-1);
    j = fib(n-2);

    //Term 2
    // #pragma omp task shared(j)
    // #pragma omp parallel task shared(j) if(n > 33)
    // #pragma omp task shared(j) if(n > 33)

    //Waiting for tasks to finish before using the returned values
    //Adds term1 + term2
    #pragma omp taskwait
    return i+j;
}