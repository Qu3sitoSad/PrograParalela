#include <iostream>
#include <omp.h>
#include <cmath>
#include <chrono>

int main() {

    int n=8;
    int A[n][n];
    int B[n][n];
    int C[n][n];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            A[i][j]= rand() % 5+1; //randoms del 1 al 10
            B[i][j]= rand() % 5+1; //randoms del 1 al 10
        }
    }
    
    printf("A:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d   ", A[i][j]);
        }
        printf("\n");
    }

    printf("B:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d   ", B[i][j]);
        }
        printf("\n");
    }

    printf("RESULTADO\n");
    #pragma omp parallel shared(C)
    {
        #pragma omp for
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                C[i][j]=0;
                for (int k=0;k<n;k++){
                    C[i][j]+= A[i][k]*B[k][j];
                } 
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d  ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
