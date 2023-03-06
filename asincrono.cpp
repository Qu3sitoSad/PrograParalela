#include <iostream>
#include <stdlib.h>
#include <mpi.h> 

int main(int argc, char ** argv){ 

    int rank; 
    int size; 
    int total_datos = 10;
    int data[10]={8,6,4,1,2,5,4,7,9,0};
    int datosPorGrupo= total_datos/2;

    MPI_Init(&argc,&argv); 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if(rank==0){ 

        int cont2=0;
        for(int i=1; i<2;i++){
                //std::printf("cont2: %d\n", cont2);
            MPI_Request request;
            MPI_Isend(&data[cont2],datosPorGrupo,MPI_INT,i,0,MPI_COMM_WORLD,&request); 
            cont2=cont2+datosPorGrupo;
        }
    
        for (int i = cont2 ; i < total_datos-1 ; i++) {
            int min = i;
            for (int j = i + 1 ; j < total_datos ; j++) {
                if (data[j] < data[min]) {
                    min = j;   
                }
            }
            if (i != min) {
                int aux = data[i];
                data[i] = data[min];
                data[min] = aux;
            }
        }

        //std::printf("B7: %d\n",B[7]); 
        int B[datosPorGrupo];
        int D[cont2];
        int val =0;
        for(int i=1;i<2;i++){
            int C[datosPorGrupo];
            
            MPI_Request request;
            MPI_Status status;
            MPI_Irecv(&C,datosPorGrupo,MPI_INT,i,0,MPI_COMM_WORLD, &request);
            MPI_Wait(&request,&status);

            for(int j = 0 ; j < datosPorGrupo  ; j++) {
                std::printf("arreglo del proceso[%d]: %d\n",i, C[j]);     
                B[val]= C[j];
                val++;
                //std::printf("val: %d\n",val);     
            } 
        }

        for(int i = cont2 ; i < total_datos  ; i++) {
            B[i]= data[i];
            std::printf("arreglo del proceso[0], i %d: %d\n",i, B[i]);
        }

         for (int i = 0 ; i < total_datos-1 ; i++) {
            int min = i;
            for (int j = i + 1 ; j < total_datos ; j++) {
                if (B[j] < B[min]) {
                    min = j;   
                }
            }
            if (i != min) {
                int aux = B[i];
                B[i] = B[min];
                B[min] = aux;
            }
        }
        
        for(int j = 0 ; j < total_datos  ; j++) {
            std::printf("B: %d\n",B[j]); 
        }


    }else{
        MPI_Request request;
        MPI_Status status;

        MPI_Irecv(&data,datosPorGrupo,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&request ); 
        MPI_Wait(&request,&status);       
        int cont=0;
        //std::printf("data: %d", data[0]);

        for (int i = 0 ; i < datosPorGrupo-1 ; i++) {
            int min = i;
            for (int j = i + 1 ; j < datosPorGrupo ; j++) {
                if (data[j] < data[min]) {
                    min = j;   
                }
            }
            if (i != min) {
                int aux = data[i];
                data[i] = data[min];
                data[min] = aux;
            }
        }

        int A[datosPorGrupo];
        for(int i = 0 ; i < datosPorGrupo  ; i++) {
            A[i]= data[i];
            //std::printf("arreglo del proceso[%d]: %d\n",rank, A[i]);
        }

        //std::printf("suma en proceso: %d igual a %d\n",rank, suma_parcial);
        
        MPI_Isend(&A,datosPorGrupo,MPI_INT,0,0,MPI_COMM_WORLD, &request);   
    }

    MPI_Finalize(); 

    return 0; 
} 
