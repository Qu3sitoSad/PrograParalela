#include <mpi.h>
#include <stdio.h>

#define ARRAY_SIZE 6

int main(int argc, char** argv) {
    int rank, size;
    int sendbuf[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int recvbuf[ARRAY_SIZE*size];  // Array para recibir datos de todos los procesos

    // Inicializar el array de datos que se enviarán
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sendbuf[i] = (rank + 1) * (i + 1);
    }

    // Recoger los datos de todos los procesos en el proceso raíz (rank 0)
    MPI_Gather(sendbuf, ARRAY_SIZE, MPI_INT, recvbuf, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprimir los datos recibidos en el proceso raíz
    if (rank == 0) {
        printf("Datos recibidos:\n");
        for (int i = 0; i < ARRAY_SIZE*size; i++) {
            printf("%d ", recvbuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
