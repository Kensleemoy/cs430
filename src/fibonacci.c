#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int input;
    char* next;
    int term;

    if (argc == 2) {
        input = strtol(argv[1], &next, 10);

        if ((next != argv[1]) && (*next == '\0')) {
            term = input;
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