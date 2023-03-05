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
        omp_set_num_threads(this->amount_threads); 
        #pragma omp parallel
        {
            #pragma omp for ordered
            for(int i=0; i<n;i++)
            {
                #pragma omp ordered
                {
                    // cout << "Num: " << omp_get_thread_num() << "\n";
                    escribir<<rand()%(posibles_elementos)+1<<",";
                }
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
        omp_set_num_threads(this->amount_threads); 
        //Llenamos el archivo INFILE con números
        #pragma omp parallel
        {
            #pragma omp for ordered
            for(int i=0; i<n;i++)
            {
                #pragma omp ordered
                {
                    escribirNumeros<<x[i]<<",";
                    // cout << "Num: " << omp_get_thread_num() << "\n";
                }
            }
            
        }
        escribirNumeros<<n<<endl;   // Se escribe la cantidad de elementos al final en el excel
        escribirNumeros.close();    //Cerramos el archivo si no lo vamos a usar nuevamente
    }
};