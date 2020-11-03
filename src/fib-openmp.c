#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>

//Declaring function prototypes
long fib(long n);

int main(int argc, char *argv[]) {
    int input, threads, time;
    char* next;
    int term, nextTerm, firstT, secondT;
    long result = 0;
    clock_t start, end;
    firstT = 0;
    secondT = 1;

    //Ensuring the correct number of arguments are there
    if (argc == 3) {

        //Grabbing input as decimal number (base 10)
        input = strtol(argv[1], &next, 10);

        //Error handling to ensure valid input
        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = input;
            threads = strtol(argv[2], NULL, 10);

            //Starts Recursive call
            // #pragma omp parallel shared(term, result) 
            // {
            //     #pragma omp single 
            //     {
            //         start = clock();
            //         result = fib(term);
            //         end = clock();
            //         time = (end - start) * 1000 / CLOCKS_PER_SEC;
            //     }
            // }

            start = clock();
            #pragma omp parallel shared(result, firstT, nextTerm, secondT, term) for num_threads(threads)
            {
                for(int i = 0; i <= term; i++) {
                    if (i == term) {
                        result = firstT;
                    }
                    nextTerm = firstT + secondT;
                    firstT = secondT;
                    secondT = nextTerm;
                }
            }
            end = clock();
            time = (end - start) * 1000 / CLOCKS_PER_SEC;
            printf("Time: %d\n", time);
            printf("The [%d] number in the Fibonacci sequence: %d\n", term, result);
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
// long fib(long n) {
//     long i, j;

    //Stop requirement --> stop creating new threads once n is a low enough value
    // if(n <= 1) {
    //     return n;
    // } else if(n <= 33) {
    //     return(fib(n-1)+fib(n-2));
    // } else {
    //     #pragma omp task shared(i) if(n > 50)
    //     {
    //         i = fib(n-1);
    //     }

    //     j = fib(n-2);
        
    //     #pragma omp taskwait
    //     {
    //         return i+j;
    //     }
    // }
    //Term 1
    // #pragma omp task shared(i)
    // #pragma omp parallel task shared(i) if(n > 33)
    

    //Term 2
    // #pragma omp task shared(j)
    // #pragma omp parallel task shared(j) if(n > 33)
    // #pragma omp task shared(j) if(n > 33)
    // j = fib(n-2);

    //Waiting for tasks to finish before using the returned values
    //Adds term1 + term2
// }