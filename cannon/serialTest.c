#include "mm.h"


int main(int arc, char** argv){

  printf("Let's make a MM!\n");

  // This isn't not adequate for testing
  // However, using the identity matrix is a good idea
  // for initial dev. 
  int Nr,Nc,Ncc;
  Nr = Nc = Ncc = 2;
  double A[]   = {1,2,3,4};
  double I22[] = {1,0,0,1};
  double C[]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


  // This is the call to matrix multiply
  int retval = mm(A,2,2,2,I22,C);
  if(retval){
    fprintf(stderr,"There was an error in MM\n");
  }




 
  // Check to see if it is right
  for(int i = 0; i< Nc; i++){
    for(int j = 0; j< Nr; j++){
      if(COMPARE(ARRAY(A,Nc,Nr,i,j),ARRAY(C,Nc,Nr,i,j))){
        fprintf(stderr,"A[%d,%dr] %lf != C[%d,%d] %lf\n",i,j, ARRAY(A,Nc,Nr,i,j),i,j,ARRAY(C,Nc,Nr,i,j));
      } 
    }
  }
  

  return 0;
}
