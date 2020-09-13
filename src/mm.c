#include <stdio.h>
#include <stdlib.h>
#include "../include/mmio.h"

int main(int argc, char *argv[])
{
    MM_typecode m1matcode;
    MM_typecode m2matcode;
    FILE *m1, *m2, *output;
    int m1M, m1N, m2M, m2N, m1Size, m2Size, outputMSize;

    if (argc != 4)
	{
		fprintf(stderr, "Usage: ./bin/mm <matrix file 1> <matrix file 2> <output file>\n");
		return(-1);
	}

    m1 = fopen(argv[1], "r");
    m2 = fopen(argv[2], "r");

    if (m1 == NULL || m2 == NULL) {
        fprintf(stderr, "Usage: ./bin/mm <matrix file 1> <matrix file 2> <output file>\n");
        return(-1);
    }

    if ((mm_read_banner(m1, &m1matcode) != 0) || (mm_read_banner(m2, &m2matcode) != 0))
    {
        fprintf(stderr, "Usage: ./bin/mm <matrix file 1> <matrix file 2> <output file>\n");
        printf("Could not process Matrix Market banner from files.\n");
        return(-1);
    }

    if (mm_is_complex(m1matcode) || mm_is_coordinate(m1matcode)) {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(m1matcode));
        return(-1);
    }

    if (mm_is_complex(m2matcode) || mm_is_coordinate(m2matcode)) {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(m2matcode));
        return(-1);
    }

    if ((mm_read_mtx_array_size(m1, &m1M, &m1N) !=0) || (mm_read_mtx_array_size(m2, &m2M, &m2N) !=0))
        return(-1);

    m1Size = m1M*m1N;
    m2Size = m2M*m2N;
    outputMSize = m1M*m2N;

    if(m1N != m2M) {
        fclose(m1);
        fclose(m2);
        fprintf(stderr, "Cannot perform matrix multiply on given matrices\n");
        return(-1);
    }

    output = fopen(argv[3], "w");

    int *matrix1[m1Size], *matrix2[m2Size], *outputMatrix[outputMSize];

    for (int i=0; i<m1N; i++) {
        for (int j=0; j<m1M; j++) {
            fscanf(m1, "%d", &matrix1[(m1N*j)+i]);
        }
    }

    for (int i=0; i<m2N; i++) {
        for (int j=0; j<m2M; j++) {
            fscanf(m2, "%d", &matrix2[(m2N*j)+i]);
        }
    }

    fclose(m1);
    fclose(m2);

    for(int i=0; i<m1N; i++) {
        for(int j=0; j < m2N; j++) {
            int sum = 0;
            for(int k=0; k < m1M; k++) {
                sum += ((int)matrix1[(i*m1N)+k] * (int)matrix2[(k*m2N)+j]);   
            }
            outputMatrix[(j*m1N)+i] = sum;
        }
    }


    mm_write_banner(output, m1matcode);
    mm_write_mtx_array_size(output, m1M, m2N);
    for (int i=0; i<outputMSize; i++)
        fprintf(output, "%d\n", outputMatrix[i]);

    fclose(output);

	return 0;
}
