#include <iostream>
#include <chrono>
#include <cmath>
#include <mpi.h>

using namespace std;

double funcion(double x){
   double f= 4.0/(1.0+pow(x,2));
   return f;
}

int main(int argc, char** argv){

    double a = 0;
    double b = 1;
    int n = 10000000;

    double h = (b-a) / n;
    double fa = funcion(a) / 2;
    double fb = funcion(b) / 2;
    int rank;
    int size;
    int* data = new int [n];

    MPI_Init(NULL,NULL);
   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        for(int i = 0 ; i < n ; i++){
            data[i] = i + 1;
        }
    }

    int datapart = n / size;
    int* local_data= new int [datapart];
    
    MPI_Scatter(data, datapart, MPI_INT, local_data, datapart, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD); 
              
    double suma = 0.0;
    for(int i = 0 ; i < datapart ; i++){
        suma = suma + funcion(a + local_data[i] * h);   
    }

    double sendbuf = suma;
    double recvbuf[size];

    MPI_Gather(&sendbuf, 1, MPI_DOUBLE, recvbuf, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double sumaTotal = 0.0;
        for (int i = 0; i < size; i++) {
            sumaTotal += recvbuf[i];
        }
        double total = (h) * (fa + sumaTotal + fb);
        printf("RESULTADO: %f ", total);
    }

    MPI_Finalize(); 
    return 0;
}
