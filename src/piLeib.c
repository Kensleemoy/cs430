#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int input;
    char* next;

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0')) {
            double upperBound = input;
            double result = 0.0;
            double sign = 1.0;
            for(int i=0; i<=upperBound; i++) {
                result += sign/(2.0*((double)i)+1.0);
                sign = -sign;
            }
            result = 4*result;
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