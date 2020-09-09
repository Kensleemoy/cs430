#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        float upperBound = atoi(argv[1]);
        float result = 0.0;
        float sign = 1.0;
        int i = 0;
        for(i=0; i<=upperBound; i++) {
            result += sign/(2.0*((float)i)+1.0);
            sign = -sign;
        }
        result = 4*result;
        printf("%lf\n", result);
        return 1;
    } else {
        printf("USAGE: ./piLeib <upper boundary for Leibniz>\n");
        return -1;
    }
}