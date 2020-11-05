#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        return -1;
    }

    int n = atoi(argv[1]);
    if(strncmp(argv[1], "0", 1) != 0 && n==0) {
        return -1;
    } 
    if(n<0) {
        fprintf(stderr, "index must be be greater than or equal to 0\n");
        return -1;
    }
    
    double pi = 1.0;

    int i = 3;
    int j = 0;

    #pragma omp parallel for private(i, j) reduction(+:pi)
    for(i=3; i <= n; i++) {
        if(i%2 == 1) {
            if(j%2 == 0) {
                pi = pi - (1.0/(double)i);
                j++;
            } else {
                pi = pi + (1.0/(double)i);
                j++;
            }
        }
    }

    pi = pi*4;
    printf("%1.6f",pi);
    return 0;
}
