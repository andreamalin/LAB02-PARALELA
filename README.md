# LAB02-PARALELA
Descargar o clonar el respositorio
'''
git clone https://github.com/andreamalin/LAB02-PARALELA
'''

<hr>

Pasos para ejecutar:
1. Dirigirse a la carpeta descargada
2. Correr el comando gcc
```
cd ./LAB02-PARALELA
g++ -o lab2 .\file.cpp .\qsortSeq.cpp -fopenmp
./lab2 n threads
```
Donde n es la cantidad de numeros aleatorios a ordenar y threads es la cantidad de hilos a utiizar
