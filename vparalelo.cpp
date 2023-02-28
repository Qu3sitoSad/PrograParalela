#include <iostream>
#include <mpi.h> 
#include <random>
#include <time.h>

//u x v = (u2v3 - u3v2, u3v1 - u1v3, u1v2 - u2v1)
//Donde u = (u1, u2, u3) y v = (v1, v2, v3)
//Si u x v = (0, 0, 0) las rectas son paralelas

int main(int argc, char ** argv){ 
    int rank; 
    int size; 
    int data[40][3];  //vector de 40 columnas 3 filas
    int parte;

    srand(time(NULL));

    int c[1][3]= {{rand() % 5+1,rand() % 5+1,rand() % 5+1}};

    MPI_Init(&argc,&argv); 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int div = 40 / size;

    for(int i=0; i<40; i++){
        for(int j=0; j<3; j++){
            data[i][j]= rand() % 5+1; //randoms del 1 al 20
        }
    }

    if(rank==0){
        
       for(int i=0; i<40; i++){
            for(int j=0; j<3; j++){
                printf("%d   ", data[i][j]);
            }
            printf("\n");
        }

        printf("valor de c: %d, %d, %d\n",c[0][0],c[0][1],c[0][2]);
        
        int aux=0;
        for(int i=1; i<size;i++){
            MPI_Send(&data[aux][0],div*3,MPI_INT,i,0,MPI_COMM_WORLD);  
            MPI_Send(&aux,1,MPI_INT,i,0,MPI_COMM_WORLD);  
            //printf("%d\n", data[aux][0]);
            //printf("%d\n", data[aux+div-1][0]);
            //printf("%d  %d \n", aux, div);
            aux=aux+div;
        }

        int uv1=0;
        int uv2=0;
        int uv3=0;
        
        for(int i = aux; i < 40; i++){

            uv1 = data[i][1]*c[0][2] - data[i][2]*c[0][1];
            uv2 = data[i][2]*c[0][0] - data[i][0]*c[0][2];
            uv3 = data[i][0]*c[0][1] - data[i][1]*c[0][0];
           
            double a1= (double) data[i][0] / (double) c[0][0];
            double a2= (double) data[i][1] / (double) c[0][1];
            double a3= (double) data[i][2] / (double) c[0][2];
            
            //printf("%d, %f, %f, %f\n",i,a1,a2,a3);

            if(a1 == a2 & a1 == a3){
                //printf("valor de c %d, %d, %d\n",c[0][0],c[0][1],c[0][2]);
                //printf("valor de data %d, %d, %d\n",data[i][0],data[i][1],data[i][2]);
               
                //printf("en el rank: %d hay una recta paralela en la posición: %d \n", rank, i+1);
                printf("respuesta : %d,", i+1);
            }
        }

        //printf("Indices con rectas paralelas:\n");
        for(int i=1; i<size; i++){
            int cont=0;
            MPI_Recv(&cont,1,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int A[cont];

            MPI_Recv(A,cont,MPI_INT,i,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for(int j=0;j< cont;j++){
                printf("respuesta : %d\n", A[j]);
            }
        }
    
    }else{
        int uv1=0;
        int uv2=0;
        int uv3=0;
        int aux=0;
        int A[10];

        MPI_Recv(data,div*3,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&aux,1,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int indice=0;
        int cont=0;
        for(int i = 0; i < div ; i++){

            uv1 = data[i][1]*c[0][2] - data[i][2]*c[0][1];
            uv2 = data[i][2]*c[0][0] - data[i][0]*c[0][2];
            uv3 = data[i][0]*c[0][1] - data[i][1]*c[0][0];

            if(uv1 == 0 & uv2 == 0 & uv3 ==0){
                //printf(" daya en la rank %d hay una recta paralela en la posición: %d \n",rank, i);
            }

            double a1= (double) data[i][0] / (double) c[0][0];
            double a2= (double) data[i][1] / (double) c[0][1];
            double a3= (double) data[i][2] / (double) c[0][2];
            
            //printf("%d, %f, %f, %f\n",i,a1,a2,a3);

            //printf("aux.%d\n", aux);
            
            if(a1 == a2 & a1 == a3){
                
                //printf("valor de data %d, %d, %d\n",data[i][0],data[i][1],data[i][2]);
                indice= aux+1+i;
                //printf("en la rank %d hay una recta paralela en la posición: %d \n",rank, indice);
                A[cont]=indice;
                cont++;
            }
        } 
        MPI_Send(&cont,1,MPI_INT,0,0,MPI_COMM_WORLD);
        MPI_Send(&A,cont,MPI_INT,0,0,MPI_COMM_WORLD); //primer 0 a donde envio segundo 0 tag.
    }

    MPI_Finalize(); 

    return 0; 
} 
