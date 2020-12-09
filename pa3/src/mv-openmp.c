#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "../include/mmio.h"

int main(int argc, char *argv[])
{
    MM_typecode matcode;
    MM_typecode vmatcode;
    FILE *m, *v, *output;
    int matrixR, matrixC, vectorSize, vectorC, matrixSize, outputSize;

    if (argc != 4)
	{
		fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
		return(-1);
	}

    if(strstr(argv[1], ".m") == NULL) {
        fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
		return(-1);
    }

    if(strstr(argv[2], ".m") == NULL) {
        fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
		return(-1);
    }

    if(strstr(argv[3], ".m") == NULL) {
        fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
		return(-1);
    }

    m = fopen(argv[1], "r");
    v = fopen(argv[2], "r");

    if ((v == NULL) || (m == NULL)) {
        fclose(m);
        fclose(v);
        fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
        return(-1);
    }

    if ((mm_read_banner(m, &matcode) != 0) || (mm_read_banner(v, &vmatcode) != 0))
    {
        fclose(m);
        fclose(v);
        fprintf(stderr, "Usage: ./bin/mm <matrix .m file> <vector .m file> <output .m file>\n");
        printf("Could not process Matrix Market banner from files.\n");
        return(-1);
    }

    if (mm_is_complex(matcode) || mm_is_coordinate(matcode)) {
        fclose(m);
        fclose(v);
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        return(-1);
    }

    if (mm_is_complex(vmatcode) || mm_is_coordinate(vmatcode)) {
        fclose(m);
        fclose(v);
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(vmatcode));
        return(-1);
    }

    if ((mm_read_mtx_array_size(m, &matrixR, &matrixC) !=0) || (mm_read_mtx_array_size(v, &vectorSize, &vectorC) !=0)) {
        fclose(m);
        fclose(v);
        return(-1);
    }

    if (vectorC != 1) {
        fclose(m);
        fclose(v);
        printf("Invalid vector file: column size must be one (1)\n");
        return (-1);
    }

    if (vectorSize != matrixC) {
        fclose(m);
        fclose(v);
        printf("Cannot perform matrix vector multiply on given matrix and vector\n");
        return(-1);
    }

    matrixSize = matrixR*matrixC;
    outputSize = vectorSize;

    output = fopen(argv[3], "w");

    int matrix[matrixSize], vector[vectorSize], outputVector[outputSize];

    for (int i=0; i<matrixC; i++) {
        for (int j=0; j<matrixR; j++) {
            fscanf(m, "%d", &matrix[(matrixC*j)+i]);
        }
    }

    for (int i=0; i<vectorSize; i++) {
            fscanf(v, "%d", &vector[i]);
    }

    fclose(m);
    fclose(v);

    #pragma omp parallel for shared (matrixC,matrixR,matrix,vector,outputVector)
    for (int i = 0; i < matrixC; i++) {
        int sum = 0;
        for (int j = 0; j < matrixR; j++) {
            sum += ((int)matrix[(j*matrixC)+i] * (int)vector[j]);
        }
        outputVector[i] = sum;
    }

    mm_write_banner(output, matcode);
    mm_write_mtx_array_size(output, vectorSize, 1);
    for (int i=0; i<outputSize; i++)
        fprintf(output, "%d\n", outputVector[i]);

    fclose(output);

	return 0;
}
