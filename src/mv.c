#include <stdio.h>
#include <stdlib.h>
#include "../include/mmio.h"

int main(int argc, char *argv[])
{
    MM_typecode matcode;
    MM_typecode vmatcode;
    FILE *m, *v, *output;
    int matrixM, matrixN, vectorSize, vectorN, matrixSize, outputSize;

    if (argc != 4)
	{
		fprintf(stderr, "Usage: ./bin/mm <matrix file> <vector file> <output file>\n");
		return(-1);
	}

    m = fopen(argv[1], "r");
    v = fopen(argv[2], "r");

    if (m == NULL || v == NULL) {
        fclose(m);
        fclose(v);
        fprintf(stderr, "Usage: ./bin/mm <matrix file> <vector file> <output file>\n");
        return(-1);
    }

    if ((mm_read_banner(m, &matcode) != 0) || (mm_read_banner(v, &vmatcode) != 0))
    {
        fclose(m);
        fclose(v);
        fprintf(stderr, "Usage: ./bin/mm <matrix file> <vector file> <output file>\n");
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

    if ((mm_read_mtx_array_size(m, &matrixM, &matrixN) !=0) || (mm_read_mtx_array_size(v, &vectorSize, &vectorN) !=0)) {
        fclose(m);
        fclose(v);
        return(-1);
    }

    if (vectorN != 1) {
        fclose(m);
        fclose(v);
        printf("Invalid vector file: column size must be one (1)\n");
        return (-1);
    }

    if (vectorSize != matrixM) {
        fclose(m);
        fclose(v);
        printf("Cannot perform matrix vector multiply on given matrix and vector\n");
        return(-1);
    }

    matrixSize = matrixM*matrixN;
    outputSize = vectorSize;

    output = fopen(argv[3], "w");

    int matrix[matrixSize], vector[vectorSize], outputVector[outputSize];

    for (int i=0; i<matrixN; i++) {
        for (int j=0; j<matrixM; j++) {
            fscanf(m, "%d", &matrix[(matrixN*j)+i]);
        }
    }

    for (int i=0; i<vectorSize; i++) {
            fscanf(v, "%d", &vector[i]);
    }

    fclose(m);
    fclose(v);

    for (int i = 0; i < matrixN; i++) {
        int sum = 0;
        for (int j = 0; j < matrixM; j++) {
            sum += ((int)matrix[(j*matrixN)+i] * (int)vector[j]);
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