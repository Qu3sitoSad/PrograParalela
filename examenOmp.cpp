#include <iostream>
#include <omp.h>
#include <chrono>

#define N 100

int serial(){
    /*
    std::vector<int> datos;
    std::ifstream is("datos.txt");
    std::string tmp;
    while(std::getline(is,tmp)){
         int valor = std::stoi(tmp);
         datos.push_back(valor);
    }*/

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

int main(){

    int num_hilos;
    int vectorA [N];
    int suma_total = 0;
    double tiempo[N];

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

    int respConteo[100];
    double tiempoT[100];
    #pragma omp parallel shared(respConteo, tiempoT)
    {

        #pragma omp for

        for(int i=0; i<N;i++){  
            auto start = std::chrono::high_resolution_clock::now();
            int cont=0;
            for(int j=0 ; j<=100; j++){
                if (vectorA[i]==j){  
                    cont++;
                }
            }
            respConteo[i]=cont++;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> tiempo = end - start;
            tiempoT[i]=tiempo.count()*0.001;        
        }
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