#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string
#include <vector>

#define INFILE "numeros.csv"
#define OUTFILE "ordered.csv"
using namespace std;

class FileHandler {
    public:
    int n;
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
        for(int i=0; i<n;i++){
            escribir<<rand()%(posibles_elementos)+1<<",";
        }

        escribir<<n<<endl;
        escribir.close();    //
    }

    void writeOutput(int *x) {
        ofstream escribirNumeros(OUTFILE,ios::out);
        if( escribirNumeros.bad() ) {
            cerr<<"Falló la creación del archivo "<<INFILE<<endl;
            exit(EXIT_FAILURE);
        }

        //Llenamos el archivo INFILE con números
        for(int i=0; i<n;i++){
            escribirNumeros<<x[i]<<",";
        }
        escribirNumeros<<n<<endl;
        escribirNumeros.close();    //Cerramos el archivo si no lo vamos a usar nuevamente
    }
};