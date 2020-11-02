#include <stdio.h>
#include <mpi.h>

#define EPS .0000001
#define COMPARE(V1,V2) V1 < V2 + EPS && V1 > V2 - EPS ? 0 : 1 
#define ARRAY(D,c,r,i,j) (D)[(i)*(r) + (j)]
#define ARRAYl(D,c,r,i,j) &((D)[(i)*(r) + (j)])
#define NAME_TO_RANK(c,r,i,j) (c)*(i) + (j)

int mm(double* A,int c,int rc,int r,double* B,double* C);
int cannon_mm(int n, int rank, int Nr, int Nc, double* A, double* B, double* C);
