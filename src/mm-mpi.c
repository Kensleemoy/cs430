#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define EPS .0000001
#define COMPARE(V1,V2) V1 < V2 + EPS && V1 > V2 - EPS ? 0 : 1 
#define ARRAY(D,c,r,i,j) (D)[(i)*(r) + (j)]
#define ARRAYl(D,c,r,i,j) &((D)[(i)*(r) + (j)])
#define NAME_TO_RANK(c,r,i,j) (c)*(i) + (j)

int mm(double* A,int c,int rc,int r,double* B,double* C);
int cannon_mm(int n, int rank, int Nr, int Nc, double* A, double* B, double* C);

int main(int argc, char** argv){
    clock_t start, end;
    int n, rank, time;
    MPI_Status status;
    int error = MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int Nr,Nc,Ncc;
    Nr = Nc = Ncc = 4;
    //---------testing 5x5 matrices---------//
    // Nr = Nc = Ncc = 5;
    // double A[]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    // double I[] =   {1,0,0,0,0,
    //                 0,1,0,0,0,
    //                 0,0,1,0,0, 
    //                 0,0,0,1,0,
    //                 0,0,0,0,1};
    // double C[]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //---------testing 4x4 matrices---------//
    double A[]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    double I[] =   {1,0,0,0,
                    0,1,0,0,
                    0,0,1,0, 
                    0,0,0,1};
    double C[]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    //Starting the clock, then timing cannon's matrix multiplication
    start = clock();
    int result = cannon_mm(n, rank, Nr, Nc, A, I, C);
    end = clock();
    time = (end - start) * 1000 / CLOCKS_PER_SEC;

    if(result){
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
            printf("Time: %d\n", time);
        }
    }

    MPI_Finalize();

    return 0;
    }

    int mm(double* A,int c,int rc,int r,double* B,double* C){

    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
        for(int k=0;k<rc;k++){
            ARRAY(C,c,r,i,j) += ARRAY(A,c,rc,i,k)*ARRAY(B,rc,r,k,j);
        }
        }
    }
    return 0;
}

int cannon_mm(int n, int rank, int Nr, int Nc, double* A, double* B, double* C){

  int dim = sqrt(n);
  int myi = rank/dim;
  int myj = rank%dim;
  MPI_Status status;

  // How much space do I need?
  int data_dim = Nr/dim;
  if(Nr%dim){
    fprintf(stderr,"Sorry! Data also has to be perfect!\n");
    return 1;
  }

  int mySize = data_dim*data_dim;
  double* localA = (double*)malloc(sizeof(double)*mySize); 
  double* localB = (double*)malloc(sizeof(double)*mySize); 
  double* localC = (double*)malloc(sizeof(double)*mySize); 
  double* tmp = (double*)malloc(sizeof(double)*mySize); 
  if(localA == NULL || localB == NULL || localC == NULL || tmp == NULL){
    fprintf(stderr,"malloc failed\n");
    return 1;
  }
 
  // Copy our data into our nice new space
  for(int i=0;i<data_dim;i++){
    for(int j=0;j<data_dim;j++){
      ARRAY(localA,data_dim,data_dim,i,j) = ARRAY(A,Nr,Nr,myi*data_dim + i,myj*data_dim +j);   
      ARRAY(localB,data_dim,data_dim,i,j) = ARRAY(B,Nr,Nr,myi*data_dim + i,myj*data_dim +j);   
      ARRAY(localC,data_dim,data_dim,i,j) = ARRAY(C,Nr,Nr,myi*data_dim + i,myj*data_dim +j);   
    }
  } 

  // Beginning of Cannon's
  // 1. Skew A (to the left)
  if(myi){  
    MPI_Request send_request,recv_request;
    // (i,j) --> (i,(i-j)%dim)
    //
    int dest = myj-myi;
    if(dest<0){
      dest = dim+dest;
    }
    dest = NAME_TO_RANK(dim,dim,myi,dest);
    MPI_Isend(localA,mySize,MPI_DOUBLE,dest,0,MPI_COMM_WORLD,&send_request);
    MPI_Irecv(tmp,mySize,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&recv_request);
    MPI_Wait(&send_request,&status);
    MPI_Wait(&recv_request,&status);
    memcpy(localA,tmp,sizeof(double)*mySize);
  }
  // 2. Skew B (up)
  //  (i,j) --> (i-j,j);
  if(myj){  
    int dest = myi-myj;
    if(dest<0){
      dest=dim+dest;
    }
    dest = NAME_TO_RANK(dim,dim,dest,myj);
    MPI_Request send_request,recv_request;
    MPI_Isend(localB,mySize,MPI_DOUBLE,dest,2,MPI_COMM_WORLD,&send_request);
    MPI_Irecv(tmp,mySize,MPI_DOUBLE,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,&recv_request);
    MPI_Wait(&send_request,&status);
    MPI_Wait(&recv_request,&status);
    memcpy(localB,tmp,sizeof(double)*mySize);
  }

  // In a Loop (multiply -> shift)
  for(int j=1;j<dim;j++){
    // do the multiplication
    int retval = mm(localA,data_dim,data_dim,data_dim,localB,localC);
    if(retval){
      fprintf(stderr,"There was an error in MM\n");
    }
    MPI_Request  send_request,recv_request;
    //shift  (i,j) --> (i,(j-1)%dim)
    int dest = myj-1;
    if(dest < 0 ){
      dest = dim+dest;
    }
    dest = NAME_TO_RANK(dim,dim,myi,dest);
    MPI_Isend(localA,mySize,MPI_DOUBLE,dest,j,MPI_COMM_WORLD,&send_request);
    MPI_Irecv(tmp,mySize,MPI_DOUBLE,MPI_ANY_SOURCE,j,MPI_COMM_WORLD,&recv_request);
    MPI_Wait(&send_request,&status);
    MPI_Wait(&recv_request,&status);
    memcpy(localA,tmp,sizeof(double)*mySize);

    //shift  (i,j) --> ((i-1)%dim,j);
    dest = myi-1;
    if(dest < 0){
      dest = dim + dest;
    }
    dest = NAME_TO_RANK(dim,dim,dest, myj);
    MPI_Isend(localB,mySize,MPI_DOUBLE,dest,j+n,MPI_COMM_WORLD,&send_request);
    MPI_Irecv(tmp,mySize,MPI_DOUBLE,MPI_ANY_SOURCE,j+n,MPI_COMM_WORLD,&recv_request);
    MPI_Wait(&send_request,&status);
    MPI_Wait(&recv_request,&status);
    memcpy(localB,tmp,sizeof(double)*mySize);
  }
  // do the multiplication
  int retval = mm(localA,data_dim,data_dim,data_dim,localB,localC);
  if(retval){
    fprintf(stderr,"There was an error in MM\n");
  }
  // End of Cannon's

  // need to collect all of the data back to rank0 and put them together
  if(rank == 0){
    for(int i=0;i<data_dim;i++){
      for(int j=0;j<data_dim;j++){
        ARRAY(C,Nr,Nr,i,j)= ARRAY(localC,data_dim,data_dim,i,j);
      }
    }
    // I get to collect the answer
    for(int r=1;r<n;r++){
      MPI_Recv(localC, mySize,MPI_DOUBLE, r, 0,MPI_COMM_WORLD,&status);
      for(int i=0;i<data_dim;i++){
        for(int j=0;j<data_dim;j++){
          ARRAY(C,Nc,Nr,((r/dim)*data_dim+i),(r%dim)*data_dim+j)= ARRAY(localC,data_dim,data_dim,i,j);
        }
      }
    }
  }else{
    MPI_Send(localC, mySize, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  
  return 0;
}