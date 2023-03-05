#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int rank, size;
    char message[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        strcpy(message, "El ganador es Juan!");
        // Soy el proceso emisor (root)
        MPI_Bcast(message, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Enviando mensaje a todos los procesos...\n");
    } else {
        MPI_Bcast(message, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Proceso %d recibió el mensaje: %s\n", rank, message);
    }

    MPI_Finalize();
    return 0;
}

