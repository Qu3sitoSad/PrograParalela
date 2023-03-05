#include <mpi.h>
#include <stdio.h>
#include <random>
#include <time.h>

#define N 8

int main(int argc, char** argv) {
    int rank, size;
    int el_max[2];
    int data[N];

    srand(time(NULL));
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int datapart= N/size;
    int local_data[datapart];

    if(rank==0){
        for(int i=0; i<N;i++){
            data[i]=rand() % 20+1;
        }
    }

    MPI_Scatter(data, datapart, MPI_INT, local_data, datapart, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD); //se asegura de que todos los procesos ya tengan su respectiva particion
    for(int i=0; i<datapart;i++){
        printf("rank: %d , %d\n", rank, local_data[i]);
    }
    
    MPI_Reduce(local_data,&el_max,2, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        //printf("El maximo es: %d\n", el_max);

        int max = el_max[0];
        for (int i = 0; i < 2; i++) {
            if (el_max[i] > max) {
                max = el_max[i];
            }
        }
        printf("Proceso %d recibió el máximo valor: %d\n", rank, max);
    }

    MPI_Finalize();
    return 0;
}