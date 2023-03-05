#include <mpi.h>
#include <stdio.h>
#include <random>
#include <time.h>

#define N 8

int main(int argc, char** argv) {
    int rank, size;
    int vectorA [N];
    int vectorB [N];
   
    srand(time(NULL));
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int datapart = N / size;
    int local_dataA[datapart];
    int local_dataB[datapart];

    if(rank==0){
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
    }

        MPI_Scatter(vectorA, datapart, MPI_INT, local_dataA, datapart, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(vectorB, datapart, MPI_INT, local_dataB, datapart, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);

        
        int op = 0;
        for(int i=0; i<datapart;i++){
            //printf("%d- %d- :\n", local_dataA[i], local_dataB[i]);
            op += local_dataA[i]*local_dataB[i];
        }
        int total=0;
        //printf("rank %d valop: %d\n", rank, op);
        MPI_Reduce(&op,&total,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if(rank==0){
            printf("Resultado: %d\n", total);
        }

    MPI_Finalize();
    return 0;
}