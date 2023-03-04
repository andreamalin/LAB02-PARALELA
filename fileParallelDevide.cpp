#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string
#include <vector>
#include <omp.h>

#define INFILE "numeros.csv"
#define OUTFILE "ordered.csv"
using namespace std;

class FileHandler {
    public:
    int n;
    int amount_threads;
    vector<string> result;

    FileHandler() {}
    void openFile() {
        ifstream lectura;
        lectura.open(INFILE);
        if( lectura.bad() ) {
            cerr<<"No se pudo leer el archivo "<<INFILE<<endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while(getline(lectura,line,',')) {
            result.push_back( line );
        }

        lectura.close();
    }

    void writeToFile() {
        ofstream escribir(INFILE,ios::out);
        if( escribir.bad() ) {
            cerr<<"Falló la creación del archivo "<<INFILE<<endl;
            exit(EXIT_FAILURE);
        }

        //Llenamos el archivo INFILE con números
        int posibles_elementos = n/2;

        // Establecemos la cantidad de hilos a utilizar por el usuario

        const int data_size = n;
        const int chunk_size = data_size / amount_threads;
        #pragma omp parallel num_threads(amount_threads)
        {
            int thread_num = omp_get_thread_num();
            int start_index = thread_num * chunk_size;
            int end_index = (thread_num == amount_threads - 1) ? data_size : (thread_num + 1) * chunk_size;
            for (int i = start_index; i < end_index; i++)
            {
                escribir<<rand()%(posibles_elementos)+1<<",";
                // cout << "Thread " << thread_num << " writing to file for i = " << i << std::endl;
            }
        }

        escribir<<n<<endl; // Se escribe la cantidad de elementos al final en el excel
        escribir.close();    //
    }

    void writeOutput(int *x) {
        ofstream escribirNumeros(OUTFILE,ios::out);
        if( escribirNumeros.bad() ) {
            cerr<<"Falló la creación del archivo "<<INFILE<<endl;
            exit(EXIT_FAILURE);
        }

        // Establecemos la cantidad de hilos a utilizar por el usuario
        //Llenamos el archivo INFILE con números
        const int data_size = n;
        const int chunk_size = data_size / amount_threads;
        #pragma omp parallel num_threads(amount_threads)
        {
            int thread_num = omp_get_thread_num();
            int start_index = thread_num * chunk_size;
            int end_index = (thread_num == amount_threads - 1) ? data_size : (thread_num + 1) * chunk_size;
            for (int i = start_index; i < end_index; i++)
            {   
                escribirNumeros<<x[i]<<",";
                // cout << "Thread " << thread_num << " writing to file for i = " << i << std::endl;
            }
        }

        escribirNumeros<<n<<endl;   // Se escribe la cantidad de elementos al final en el excel
        escribirNumeros.close();    //Cerramos el archivo si no lo vamos a usar nuevamente
    }
};