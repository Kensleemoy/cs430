#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>

/**
 * writeOutput
 * 
 * Write Mandelbrot image in PGM format
 * 
 * @param fileName - Filename to write PGM data
 * @param data - output array data (Mandelbrot pixels)
 * @param width - image width
 * @param height - image height
 * 
 * */
 void writeOutput(const char *fileName, BYTE *data, int width, int height) {
    int i,j;
    int max = -1;
    int size = width*height;

    for (i=0; i < size; ++i) {
        if(data[i] > max) {
            max = data[i];
        }
    }

    FILE *fout = fopen(fileName, "w");

    fprintf(fout, "P2\n");
    fprintf(fout, "%d\t%d\n", width, height);
    fprintf(fout, "%d\n", max);

    for (i=0; i < height; ++i) {
        for (j=0; j<width; ++j) {
            fprintf(fout, "%d\t", data[i*width+j]);
        }
        fprintf(fout,"\n");
    }

    fflush(fout);
    fclose(fout);
}

void main() {
    
}