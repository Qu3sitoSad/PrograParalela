#include <mpi.h>
#include <stdio.h>
#include <random>
#include <chrono>
#include <time.h>

#define N 100

int main(int argc, char** argv) {
    
    int rank, size;
    /*
    std::vector<int> datos;
    std::ifstream is("datos.txt");
    std::string tmp;
    while(std::getline(is,tmp)){
         int valor = std::stoi(tmp);
         datos.push_back(valor);
    }*/
   
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
            MPI_Recv(respConteo,N,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(tiempo,N,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
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

        int total[N];
        double t_total[N];
        for(int i=0; i<N; i++){
            total[N] += respConteo[i];
            t_total[N] += tiempoT[i];
        }

        for(int i=0; i<N; i++){
            printf("%d |%d |%lf \n",i, total[i], t_total[i]); 
        }
                    
    }else{

        MPI_Recv(vectorA,datapart,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int respConteo[100];
        double tiempoT[100];
        int cont=0;

        for(int i=0; i<N; i++){   
            auto start = std::chrono::high_resolution_clock::now();
            int cont=0;
            for(int j=0; j<=100; j++){
                if (vectorA[i]==j){  
                    cont++;
                }
            }
            respConteo[i]=cont++;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> tiempo = end - start;
            tiempoT[i] = tiempo.count()*0.001;        
        }
                
        //int total[N];
        //int t_total[N];
        //MPI_Reduce(respConteo,total,100, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        //MPI_Reduce(tiempoT,t_total,100, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Send(respConteo,N,MPI_INT,0,0,MPI_COMM_WORLD);
        MPI_Send(tiempoT,N,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
