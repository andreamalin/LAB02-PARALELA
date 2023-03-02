// Ejemplo de QuickSort
#include <stdlib.h>
#include <stdio.h>
#include <string>       //string
#include "file.cpp"

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

  int thread_num = 1;
  if (argc == 1) {
      printf("Hace falta el tamanio n de la lista\n");
      exit (1);
  } else if (argc == 2) {
      printf("Warning: Hace falta la cantidad de threads\n");
      thread_num = atoi(argv[2]);
  }
  const int n = atoi(argv[1]);

  //allocate the array
  int *arr = (int *)malloc(n * sizeof(int));
  file.n = n;
  file.writeToFile();
  file.openFile();

  int j;
  while (j < n) {
    int numero = stoi(file.result[j]);  //Debemos convertir el string a int
    arr[j] = numero;
    j += 1;
  }

  //---- Inicialización con elementos aleatorios entre 1-N/2
  //TODO aca leer de archivo CSV, generando random para ejemplo
  printf("Generando lista random con %d elementos\n", n);

  // Recibe lista, 0, cantidad de elementos
  par_qsort(arr, 0, n-1);
  

  printf("Primeros Elementos: %d, %d, %d\n", arr[0], arr[1], arr[2]);
  printf("Medios Elementos: %d, %d, %d\n", arr[n/4], arr[n/4 +1], arr[n/4 +2]);
  printf("Ultimos Elementos: %d, %d, %d\n", arr[n-3], arr[n-2], arr[n-1]);
  

  file.writeOutput(arr);

  //deallocate the array
  delete[] arr;

  return 0;
}
