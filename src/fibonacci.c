#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int input;
    char* next;
    int term;
    int firstT = 0;
    int secondT = 1;
    int nextTerm = 0;
    int result = 0;

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0') && (input >= 0)) {
            term = input;
            
            for(int i = 0; i <= term; i++) {
                printf("%d, ", firstT);
                if (i == term) {
                    result = firstT;
                }
                nextTerm = firstT + secondT;
                firstT = secondT;
                secondT = nextTerm;
            }
            printf("\nThe [%d] number in the Fibonacci sequence: %d\n", term, result);
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