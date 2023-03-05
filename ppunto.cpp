#include <mpi.h>
#include <stdio.h>
#include <random>
#include <time.h>

#define N 8

int main(int argc, char** argv) {
    int rank, size;
   
    srand(time(NULL));
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int datapart= N/size;
    int* vectorA = new int[N];
    int* vectorB = new int[N];

    if(rank==0){

        //int* vectorA = new int[N];
        //int* vectorB = new int[N];

        for(int i=0; i<N; i++){
            vectorA[i]= rand() % 10+1;
            vectorB[i]= rand() % 10+1;
        }

        printf("vectorA:\n");
        for(int i=0; i<N;i++){
            printf("%d, ", vectorA[i]);
        }
        printf("\n");
        printf("vectorB:\n");
        for(int i=0; i<N;i++){
            printf("%d, ", vectorB[i]);
        }

        int aux=0;
        //printf("dataa%d", datapart);
        for(int i=1;i<size;i++){
            MPI_Send(&vectorA[aux],datapart,MPI_INT,i,0,MPI_COMM_WORLD);  
            MPI_Send(&vectorB[aux],datapart,MPI_INT,i,0,MPI_COMM_WORLD);  
            //printf("- %d ", vectorA[aux]);
            aux += datapart;
        }

        int suma=0;
        for(int i=1;i<size;i++){
            int op=0;
            MPI_Recv(&op,1,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //printf("recibe %d\n, ", op);
            suma += op;
        }

        int op0=0;
        //printf("valor de aux: %d", aux);
        for(int i=aux; i<N;i++){
            op0 += vectorA[i]*vectorB[i];
        }
        printf("\n");
        printf("resultado: %d\n", suma+ op0);
    }else{

        MPI_Recv(vectorA,datapart,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vectorB,datapart,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //vectorA = new int[datapart];

        int op = 0;
        for(int i=0; i<datapart;i++){
            op += vectorA[i]*vectorB[i];
            //printf("rank: %d, %d, ",rank, vectorA[i]);
        }
        //printf("rank %d ,envio %d\n, ",rank, op);
        MPI_Send(&op,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}