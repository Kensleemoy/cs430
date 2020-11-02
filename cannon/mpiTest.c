#include <stdlib.h>
#include "mm.h"
#include <mpi.h>
#include <math.h>
#include <string.h>


int main(int argc, char** argv){

  int n, rank;
  MPI_Status status;
  int error = MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // These data are the full global data
  // We are now only responsible for a portion of the data
  // Let's grab just our own data for the MM
  int Nr,Nc,Ncc;
  Nr = Nc = Ncc = 4;
  double A[]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  double I[] =   {1,0,0,0,
                  0,1,0,0,
                  0,0,1,0, 
                  0,0,0,1};
  double C[]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


  //Actual call to matrix multiply
  if(cannon_mm(n, rank, Nr, Nc, A, I, C)){
    fprintf(stderr, "ERROR\n");
  }else{
    if(!rank){
      int error = 0;
      // Check to see if it is right
      for(int i = 0; i< Nc; i++){
        for(int j = 0; j< Nr; j++){
          if(COMPARE(ARRAY(A,Nc,Nr,i,j),ARRAY(C,Nc,Nr,i,j))){
            error++;
            fprintf(stderr,"A[%d,%d] %lf != C[%d,%d] %lf\n",i,j, ARRAY(A,Nc,Nr,i,j),i,j,ARRAY(C,Nc,Nr,i,j));
          } 
        }
      }
      if(!error){
        printf("SUCCESS\n");
      }
    }
  }

  MPI_Finalize();

  return 0;
}
