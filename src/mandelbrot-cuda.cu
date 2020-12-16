#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>

typedef unsigned char BYTE;

#define IMAGE_SIZE 6*1000*1000
#define MAXITER 1000
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
   double xmin = -2;
   double xmax = 1;
   double ymin = -1.5;
   double ymax = 1.5;

   FILE *fp = fopen(fileName, "wb");
    fprintf(fp,"P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n", xmin, xmax, ymin, ymax, MAXITER, X_RES, Y_RES, (MAXITER < 256 ? 256 : MAXITER));
    fwrite(image, 1, IMAGE_SIZE, fp);
    fclose(fp);
}

__global__ void mandelbrot(BYTE* image,uint16_t maxiter){
    	double xmin = -2;
    	double xmax = 1;
    	double ymin = -1.5;
    	double ymax = 1.5;
    	double dx = (xmax-xmin)/X_RES;
    	double dy = (ymax-ymin)/Y_RES;

	//int index_x = blockIdx.x * blockDim.x + threadIdx.x;
	//int index_y = blockIdx.y * blockDim.y + threadIdx.y;
	//int grid_width = gridDim.x * blockDim.x;
	//int index = index_x * grid_width + index_y;

	//int j = blockIdx.x * blockIdx.y;
	int j = blockIdx.y * gridDim.x + blockIdx.x;
	//int i = threadIdx.x * threadIdx.y;
	int i = threadIdx.y * blockDim.x + threadIdx.x;

	double x = xmin + i * dx;
	double y = ymax - j * dy;

	int k;
	double u = 0.0;
	double v = 0.0;
	double u2 = u*u;
	double v2 = v*v;

        for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
	}
	
	int pxlStartLoc = 6*((j*X_RES)+i);
	//int pxlStartLoc = 6*(index);
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
	dim3 grid_dim(100,10,1);
	dim3 block_dim(100,10,1);

	cudaMallocManaged(&image, IMAGE_SIZE);	
	mandelbrot<<<grid_dim,block_dim>>>(image,MAXITER);
	cudaDeviceSynchronize();

	writeOutput(argv[1],image,X_RES,Y_RES);
	cudaFree(image);
	return 0; 
}
