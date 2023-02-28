#Ejemplo MPI

#Instalación
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
