#include <iostream>
#include <mpi.h> 
#include <random>
#include <time.h>

int main(int argc, char ** argv){ 
    int rank; 
    int size; 
    int n=4;
    int A[n][n];  //vector de 40 columnas 3 filas
    int B[n][n];

    srand(time(NULL));

    MPI_Init(&argc,&argv); 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int div = n / size;

    if(rank==0){
        
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                A[i][j]= rand() % 5+1; //randoms del 1 al 10
                B[i][j]= rand() % 5+1; //randoms del 1 al 10
            }
        }
        
        printf("A:\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                printf("%d   ", A[i][j]);
            }
            printf("\n");
        }

        printf("B:\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                printf("%d   ", B[i][j]);
            }
            printf("\n");
        }
       
        int aux=0;
        for(int i=1; i<size;i++){
            MPI_Send(&A[aux][0],div*n,MPI_INT,i,0,MPI_COMM_WORLD);  
            MPI_Send(&B, n*n, MPI_INT,i,0,MPI_COMM_WORLD);
            aux=aux+div;
        }

         for(int i=1; i<size; i++){
            int C[div][n];
           // MPI_Recv(C,div*n,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            /*for(int j=0;j< cont;j++){
                printf("respuesta : %d\n", A[j]);
            }*/
        }

    }else{
        MPI_Recv(A,div*n,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B,n*n,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("rank %d , %d , %d\n", rank, A[0][0],A[div-1][0]);
        printf("rank %d , %d , %d\n", rank, B[0][0],B[n][n]);

        int C[div][n];
        for(int i=0; i<div; i++){
            for(int j=0; j<n; j++){
                C[i][j]=0;
                for (int k=0;k<n;k++){
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
                } 
            }
        }
       // MPI_Send(&C,div*n,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    MPI_Finalize(); 
    return 0; 
}