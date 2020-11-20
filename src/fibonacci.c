#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int input;
    char* next;
    int term;
    int firstT = 0;
    int secondT = 1;
    int nextTerm = 0;
    int result = 0;
    clock_t start, end;
    double time;         //this will be used for timing for the report

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = input;
            
            start = clock();
            for(int i = 0; i <= term; i++) {
                if (i == term) {
                    result = firstT;
                }
                nextTerm = firstT + secondT;
                firstT = secondT;
                secondT = nextTerm;
            }
            end = clock();
            time = ((double)(end - start)) / (double)CLOCKS_PER_SEC;
            printf("Time: %f\n", time);
            printf("The [%d] number in the Fibonacci sequence: %d\n", term, result);
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