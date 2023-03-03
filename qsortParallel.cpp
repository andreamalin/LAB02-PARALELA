// Ejemplo de QuickSort
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include <string>       //string
#include "fileParallel.cpp"

void par_qsort(int *data, int lo, int hi) 
{
  if(lo > hi) return;
  int l = lo; // El indice mas pequenio
  int h = hi; // El indice más grande
  int p = data[(hi + lo)/2]; // Elefimos el pivote como el valor enmedio entre el rando de h y l

  while(l <= h){
    // Cuando el valor actual es menor que el pivote
    while((data[l] - p) < 0) l++; // Incrementamos el indice del elemento pequenio
    // Cuando el valor actual es mayor que el pivote
    while((data[h] - p) > 0) h--;  // Disminuimos el indice del elemento mayor

    // Mientras el valor de la izquierda sea mas pequenio que el de la derecha
    if(l<=h){
      // swap dejamos los elementos mas peqenios a la izq y los mas grandes a la derecha (en comparacion al pivote)
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      // actualizamos los indices
      l++; h--;
    }
  }

  // Llamamos de forma recursiva
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}


int main (int argc, char *argv[]){
  FileHandler file;
  int thread_num;

  if (argc == 1) {
    printf("Hace falta el tamanio n de la lista\n");
    exit (1);
  } else if (argc == 2) {
    printf("Warning: Hace falta la cantidad de threads\n");
    thread_num = 1;
  } else {
    // Si si viene tomamos su valor, de lo contrario sera 1
    thread_num = atoi(argv[2]);
  }
  const int n = atoi(argv[1]);

  //allocate the array
  int *arr = (int *)malloc(n * sizeof(int));
  file.n = n;
  file.amount_threads = thread_num;
  double t_init = omp_get_wtime();

  file.writeToFile();
  file.openFile();
  double t_fin = omp_get_wtime();

  int j;
  while (j < n) {
    int numero = stoi(file.result[j]);  //Debemos convertir el string a int
    arr[j] = numero;
    j += 1;
  }


  // Recibe lista, 0, cantidad de elementos
  par_qsort(arr, 0, n-1);
  

  double delta = t_fin - t_init;

  printf("\nCon n threads = %d y con lista n = %d",thread_num, n);
  printf("\n\nCon tiempo = %f",delta);
  printf("\nCon precision = %f", omp_get_wtick());

  file.writeOutput(arr);

  //deallocate the array
  delete[] arr;

  return 0;
}
