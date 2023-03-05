#include <iostream>
#include <omp.h>

#define N 8
int main(){

    int num_hilos;
    int vectorA [N];
    int vectorB [N];
    int suma_total = 0;

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

    #pragma omp parallel
    {
    #pragma omp master
        num_hilos = omp_get_num_threads();
    }

    int sumas[num_hilos];
    #pragma omp parallel shared(sumas)
    {
        int tid = omp_get_thread_num();
        sumas[tid] = 0;
        #pragma omp for
        for(int i=0;i<N;i++){
            sumas[tid] += vectorA[i] * vectorB[i];
        }
    }

    for(int i=0;i<num_hilos;i++){
        suma_total += sumas[i];
    }
    printf("\n");
    printf("RESULTADO: %d",suma_total);

    return 0;
}