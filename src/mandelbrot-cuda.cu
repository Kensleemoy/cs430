#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>

typedef unsigned char BYTE;

#define IMAGE_SIZE 6*1000*1000
#define X_RES 1000
#define Y_RES 1000

/**
 * writeOutput
 * 
 * Write Mandelbrot image in PGM format
 * 
 * @param fileName - Filename to write PGM image
 * @param image - output array image (Mandelbrot pixels)
 * @param width - image width
 * @param height - image height
 * 
 * */
 void writeOutput(const char *fileName, BYTE *image, int width, int height) {
    int i,j;
    int max = -1;
    int size = width*height;

    for (i=0; i < size; ++i) {
        if(image[i] > max) {
            max = image[i];
        }
    }

    FILE *fout = fopen(fileName, "w");

    fprintf(fout, "P2\n");
    fprintf(fout, "%d\t%d\n", width, height);
    fprintf(fout, "%d\n", max);

    for (i=0; i < height; ++i) {
        for (j=0; j<width; ++j) {
            fprintf(fout, "%d\t", image[i*width+j]);
        }
        fprintf(fout,"\n");
    }

    fflush(fout);
    fclose(fout);
}

__global__ void mandelbrot(BYTE* image,uint16_t maxiter,double u,double v,double x,double y){
	int k;
	double u2 = u*u;
	double v2 = v*v;
    	double xmin = -2;
    	double xmax = 1;
    	double ymin = -1.5;
    	double ymax = 1.5;
    	double dx = (xmax-xmin)/X_RES;
    	double dy = (ymax-ymin)/Y_RES;

        for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
	}

	int pxlStartLoc = 6*((j*xres)+i);//TODO Calculate index for CUDA
	if (k >= maxiter) {
		image[pxlStartLoc+0] = 0;
        	image[pxlStartLoc+1] = 0;
        	image[pxlStartLoc+2] = 0;
        	image[pxlStartLoc+3] = 0;
        	image[pxlStartLoc+4] = 0;
        	image[pxlStartLoc+5] = 0;
      	}
	else {
        	image[pxlStartLoc+0] = k >> 8;
        	image[pxlStartLoc+1] = k & 255;
        	image[pxlStartLoc+2] = k >> 8;
        	image[pxlStartLoc+3] = k & 255;
        	image[pxlStartLoc+4] = k >> 8;
        	image[pxlStartLoc+5] = k & 255;
	}	
}

int main(int argc, char* argv[]) {
	

	BYTE* image;
	dim3 grid_dim(100,1,1);//TODO gridDim
	dim3 block_dim(10,1,1);//TODO blockDim

	cudaMalloc(&image, IMAGE_SIZE);	
	mandelbrot<<<grid_dim,block_dim>>>(image,1000,?,?,?,?);//TODO add dimensions
	cudaDeviceSynchronize();

	writeOutput(argv[1],image,X_RES,Y_RES);
	cudaFree(image)
	return 0; 
}
