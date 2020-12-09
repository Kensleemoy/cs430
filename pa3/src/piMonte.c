#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int darts = 10;
    int hit = 0;
    int total = 0;
    double x;
    double y;
    double result = 0.0;
    double distance;
    
    srand(time(NULL));
    for(int i = 0; i < (darts * darts); i++) {
        x = (double)(rand() % (darts + 1))/darts;
        y = (double)(rand() % (darts + 1))/darts;

        distance = (x * x) + (y * y);

        if (distance <= 1) {
            hit++;
        }

        total++;

        result = ((double)(4*hit)/total);
    }
    printf("%lf\n", result);
    return 0;
}