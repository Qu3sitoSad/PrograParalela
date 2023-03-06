#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>

#define N 100

int main(){
    int vectorA[N];
    int respConteo[N];
    double tiempoT[N];

    for(int i=0; i<N; i++){
        vectorA[i]= rand() % N+0;
    }

    printf("vectorA:\n");
    for(int i=0; i<N;i++){
        printf("%d, ", vectorA[i]);
    }

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

    int total[N];
    double t_total[N];
    for(int i=0; i<N; i++){
        total[N] += respConteo[i];
        t_total[N] += tiempoT[i];
    }

    for(int i=0; i<N; i++){
        printf("%d |%d |%lf \n",i, total[i], t_total[i]); 
    }
    return 0;
}