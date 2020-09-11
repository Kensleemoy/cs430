/* 
*   Matrix Market I/O example program
*
*   Create a small sparse, coordinate matrix and print it out
*   in Matrix Market (v. 2.0) format to standard output.
*
*   (See http://math.nist.gov/MatrixMarket for details.)
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/mmio.h"

#define nz 4
#define M 10
#define N 10

int main()
{
    FILE *myFile;
    myFile = fopen("./IOfiles/output.m", "w");
    MM_typecode matcode;                        
    int I[nz] = { 0, 4, 2, 8 };
    int J[nz] = { 3, 8, 7, 5 };
    double val[nz] = {1.1, 2.2, 3.2, 4.4};
    int i;

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(myFile, matcode); 
    mm_write_mtx_crd_size(myFile, M, N, nz);

    /* NOTE: matrix market files use 1-based indices, i.e. first element
      of a vector has index 1, not 0.  */

    for (i=0; i<nz; i++) {
        fprintf(myFile, "%d %d %10.3g\n", I[i]+1, J[i]+1, val[i]);
    }
    fclose(myFile);

    printf("Matrix has been written to [ IOfiles/output.m ]\n");

	return 0;
}
