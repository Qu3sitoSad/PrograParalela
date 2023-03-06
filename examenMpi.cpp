#include <mpi.h>
#include <stdio.h>
#include <random>
#include <chrono>
#include <time.h>

#define N 100

int main(int argc, char** argv) {
    
    int rank, size;
   
    srand(time(NULL));
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int datapart= N/size;
    int* vectorA = new int[N];

    if(rank==0){

        for(int i=0; i<N; i++){
            vectorA[i]= rand() % N+0;
        }

        printf("vectorA:\n");
        for(int i=0; i<N;i++){
            printf("%d, ", vectorA[i]);
        }
        
        int aux=0;
        for(int i=1;i<size;i++){
            MPI_Send(&vectorA[aux],datapart,MPI_INT,i,0,MPI_COMM_WORLD);  
            aux += datapart;
        }

        for(int i=1;i<size;i++){
            int respConteo[N];
            int tiempo;
            MPI_Recv(respConteo,N,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(tiempo,1,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //prinf("tiempo: ", tiempo);
        }

        //rank0
        int respConteo[100];
        for(int i=0; i<datapart;i++){   
            int cont=0;
            for(int j=0 ; j<=100; j++){
                if (vectorA[i]==j){  
                    cont++;
                }
            }
            respConteo[i]=cont++;
        }

        for(int i=0;i<100;i++){
            printf("val: %d, #r: %d\n", i, respConteo[i]);
        }

        int ContTotal[N];
        for(int i=0;i<size;i++){
            for(int j=0; j<N;j++){
                ContTotal[j] += respConteo[j]; 
            }
        }
        
        for(int j=0; j<100;j++){
            printf("%d , %d\n",j, ContTotal[j]);
        }
        

    }else{

        MPI_Recv(vectorA,datapart,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int respConteo[100];
        int cont=0;

        //auto start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<datapart;i++){   
            int cont=0;
            for(int j=0 ; j<=100; j++){
                if (vectorA[i]==j){  
                    cont++;
                }
            }
            respConteo[i]=cont++;
        }
        //auto end = std::chrono::high_resolution_clock::now();

        //std::chrono::duration<double> tiempo = end - start;

        for(int i=0;i<N;i++){
            printf("val: %d, #r: %d\n", i, respConteo[i]);
        }

        MPI_Send(respConteo,100,MPI_INT,0,0,MPI_COMM_WORLD);
        //MPI_Send(&tiempo,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);

    }
    MPI_Finalize();
    return 0;
}
