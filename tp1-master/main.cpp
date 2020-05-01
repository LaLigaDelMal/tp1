//============================================================================
// Name        : tp1-master
// Author      :
// Version     : 0.2
// Description : primer parcial de algoritmos y estructuras de datos
//============================================================================

#include <iostream>
#include "Pila.cpp"
#include "Nodo.cpp"
#include "Lista.cpp"
#include <fstream>

using namespace std;

int main() {

      cout << "Lectura de un archivo html" << endl;

      string linea;
    	fstream file;

      file.open("archivo.html");

      if(file.is_open()) {
        while( !file.eof() ){
  		      getline(file, linea);                       //funcion de string
            cout << linea << '\n';
  	    }
        file.close();
      }
      else
        cout << "ERROR! -> El archivo no pudo ser abierto.";


    return 0;
}
