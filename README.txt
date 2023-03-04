##Instalación MPI
```
sudo apt-get update 
sudo apt-get install libopenmpi-dev
```

#Verificar
```
mpiexec --version
```

#Compilar
```
mpicxx main.cpp ejemplo01
```

#Ejecutar
```
mpiexec -n 4 ./ejemplo01
```

##Instalacion OMP en ubuntu 
```
sudo apt-get update 
sudo apt-get install libopenmpi-dev

```
#Compilar 
```
g++ -fopenmp archivo.cpp -o archivo
```

#Ejecutar
```
./archivo
```