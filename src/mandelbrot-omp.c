/*
   This program is and adaptation of serial mandelbrot from:
   https://gist.github.com/andrejbauer/7919569
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define IMAGE_SIZE 6*1000*1000

unsigned char image[IMAGE_SIZE];

int main(int argc, char* argv[])
{
  /* Parse the command line arguments. */
  if (argc != 2) {
    printf("Usage:   %s <out.ppm>\n", argv[0]);
    printf("Example: %s pic.ppm\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* The window in the plane. */
  const double xmin = -2;
  const double xmax = 1;
  const double ymin = -1.5;
  const double ymax = 1.5;

  /* Maximum number of iterations, at most 65535. */
  const uint16_t maxiter = 1000;

  /* Image size, width is given, height is computed. */
  const int xres = 1000;
  const int yres = 1000;

  /* The output file name */
  const char* filename = argv[1];

  /* Open the file and write the header. */
  FILE * fp = fopen(filename,"wb");

  /*write ASCII header to the file*/
  fprintf(fp,
          "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  int i,j; /* Pixel counters */

//#pragma omp parallel for private(i,j) shared(dx,dy,fp)
  for (j = 0; j < yres; j++) {
    double y = ymax - j * dy;

    #pragma omp parallel for shared(i,fp)
    for(i = 0; i < xres; i++) {
      double u = 0.0;
      double v= 0.0;
      double x = xmin + i * dx;
      double u2 = u*u;
      double v2 = v*v;
      int k = 0;
	    
      for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
      };

      int pxlStartLoc = 6*((j*xres)+i);
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
      };
    }
  }

  fwrite(image, 1, IMAGE_SIZE, fp);
  fclose(fp);
  return 0;
}
