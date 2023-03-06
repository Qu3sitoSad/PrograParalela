#include <iostream>
#include <omp.h>
#include <chrono>

namespace ch = std::chrono;

#define N 100

int serial(){
    for(int i=0; i<datapart;i++){   
        int cont=0;
        for(int j=0 ; j<=100; j++){
            if (vectorA[i]==j){  
                cont++;
            }
        }
        respConteo[i]=cont++;
    }
    for(int i=0;i<N;i++){
        printf("valor: %d, #repeticiones: %d ", i, respConteo[i]);
    }
}
int main(){

    int num_hilos;
    int vectorA [N];
    int suma_total = 0;

    for(int i=0; i<N; i++){
        vectorA[i]= rand() % N+1;

    }
        
    printf("vectorA:\n");
    for(int i=0; i<N;i++){
        printf("%d, ", vectorA[i]);
    }

    #pragma omp parallel
    {
    #pragma omp master
        num_hilos = omp_get_num_threads();
    }

    int respConteo[num_hilos];
    #pragma omp parallel shared(respConteo)
    {
        auto start = ch::high_resolution_clock::now();
        int tid = omp_get_thread_num();
        respConteo[tid] = 0;
        #pragma omp for

        for(int i=0; i<N;i++){   
            int cont=0;
            for(int j=0 ; j<=100; j++){
                if (vectorA[i]==j){  
                    cont++;
                }
            }
            respConteo[i]=cont++;
        }
        auto end = ch::high_resolution_clock::now();
        ch::duration<double, std::milli> tiempo = end - start;
    }

    int ContTotal[100];
    for(int i=0;i<num_hilos;i++){
        for(int j=0; j<100;j++){
            ContTotal += respConteo[i];
        }
    }

    for(int j=0; j<100;j++){
        printf("%d , %d",i, ContTotal[i]);
    }

    return 0;
}