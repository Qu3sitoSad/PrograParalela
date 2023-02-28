#include <iostream>
#include <mpi.h> 
#include <random>
#include <time.h>

int main(int argc, char ** argv){ 
    int rank; 
    int size; 
    int numConsecutivo= 8;  
    int data[numConsecutivo][3];

    int cTotal = numConsecutivo * 3;
    
    int pa=0;
    int im=0;
    int impar[1024];
    int par[1024];
    
    srand(time(NULL));

    MPI_Init(&argc,&argv); 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int div = (numConsecutivo*3) / 2;

    if(rank==0){    

        int cont=0;
        for(int i=0; i<numConsecutivo; i++){
            for(int j=0; j<3;j++){
                data[i][j]=cont;
                cont++;
            }
        }

        for(int i=0; i<numConsecutivo; i++){
            for(int j=0; j<3;j++){
                printf(" %d ",data[i][j]);
            }
            printf("\n");
        }
        
        for(int i=0; i<numConsecutivo; i++){
            for(int j=0; j<3;j++){
                if(data[i][j]%2==0){
                    par[pa]=data[i][j];
                    pa++;	            
                }else{
                    impar[im]=data[i][j];
                    im++;				
                }
            }
        }
        
        MPI_Send(&par,div,MPI_INT,1,0,MPI_COMM_WORLD);  
        MPI_Send(&impar,div,MPI_INT,2,0,MPI_COMM_WORLD);  

    }else if(rank==1){
       MPI_Recv(par,div,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       printf("la rank %d recibio: ", rank);
        for(int i=0; i<div; i++){
            printf("%d, ",par[i]);
        }
        printf("\n");

    }else if(rank==2){
        MPI_Recv(impar,div,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("la rank %d recibio: ", rank);
        for(int i=0; i<div; i++){
            printf("%d,",impar[i]);
        }
        printf("\n");
        
    }
        
    MPI_Finalize(); 

    return 0; 
} 