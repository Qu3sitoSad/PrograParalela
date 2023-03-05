#include <iostream>
#include <mpi.h> 
#include <random>
#include <time.h>
#include <math.h>

int main(int argc, char ** argv){ 
    int rank; 
    int size; 
    int n=10;
    int data[n][3];  //vector de 40 columnas 3 filas
    int C[3][3];


    int x;
    int y;
    int z;
    int potencia = 2;
    int elmenor = 999;
    int aux2;
    int res;
      

    srand(time(NULL));

    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int div = n / size;

    if(rank==0){

         for(int i=0; i<n; i++){
            for(int j=0; j<3; j++){
                data[i][j]= rand() % 10+1; //randoms del 1 al 10
            }
        }

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                C[i][j]= rand() % 10+1; //randoms del 1 al 10
            }
        }
        
        printf("data:\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<3; j++){
                printf("%d   ", data[i][j]);
            }
            printf("\n");
        }

        printf("\n");
        printf("C:\n");
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                printf("%d   ", C[i][j]);
            }
            printf("\n");
        }
       
        int aux=0;
        for(int i=1; i<size;i++){
            MPI_Send(&data[aux][0],div*3,MPI_INT,i,0,MPI_COMM_WORLD);  
            //MPI_Send(&c, 9, MPI_INT,i,0,MPI_COMM_WORLD);
            //printf("%d\n", data[aux][0]);
            //printf("%d\n", data[aux+div-1][0]);
            //printf("%d , %d \n", aux, div);
            aux=aux+div;
        }

        MPI_Bcast(C, 9, MPI_INT, 0, MPI_COMM_WORLD);

        int indices[div];
        for(int i = aux; i < div; i++){
            elmenor = 999; // Reiniciar el valor de elmenor en cada iteración
            for(int j = 0; j < 3; j++){
                x = pow(data[i][j] - C[0][j], potencia);
                y = pow(data[i][j] - C[1][j], potencia);
                z = pow(data[i][j] - C[2][j], potencia);

                res = sqrt(x + y + z); // Corregir el cálculo de la distancia
                if(res < elmenor){
                    elmenor = res;
                    aux2 = j;
                }
            }
            indices[i] = aux2; // Actualizar el valor de indices en cada iteración
        }

        printf("Resultado: \n");
        int cont=0;
        for(int i=1; i<size; i++){
            int indices[div];
            MPI_Recv(indices,div,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("Rank: %d\n", i);
            for(int j=0; j<div; j++){
                printf("(%d %d %d) | %d \n",data[cont][0],data[cont][1],data[cont][2], indices[j]);
                cont++;
            }            
        }
        printf("Rank: 0\n");
        for(int j=aux; j<n; j++){
            printf("(%d %d %d) | %d \n",data[j][0],data[j][1],data[j][2], indices[j]);
        } 

    }else{
        MPI_Recv(data,div*3,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Bcast(C, 9, MPI_INT, 0, MPI_COMM_WORLD);
        //printf("rank %d , %d , %d\n", rank, data[0][0],data[div-1][0]);
        
        /*for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                printf("%d  ", C[i][j]);
            }
            printf("\n");
        }*/

        
        int indices[div];
        for(int i = 0; i < div; i++){
            elmenor = 999; // Reiniciar el valor de elmenor en cada iteración
            for(int j = 0; j < 3; j++){
                x = pow(data[i][j] - C[0][j], potencia);
                y = pow(data[i][j] - C[1][j], potencia);
                z = pow(data[i][j] - C[2][j], potencia);

                res = sqrt(x + y + z); // Corregir el cálculo de la distancia
                if(res < elmenor){
                    elmenor = res;
                    aux2 = j;
                }
            }
            indices[i] = aux2; // Actualizar el valor de indices en cada iteración
        }

        /*for(int j = 0; j < div; j++){
            printf("%d ", indices[j]);
        }*/

        MPI_Send(indices,div,MPI_INT,0,0,MPI_COMM_WORLD);
    }
        
    MPI_Finalize(); 
    return 0; 
}

