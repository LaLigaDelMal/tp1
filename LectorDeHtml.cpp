//////////// Implementacion de la clase LectorDeHtml

//#include "LectorDeHtml.h"
#ifndef AYED_PROGRAMA_LECTORDEHTML_H
#define AYED_PROGRAMA_LECTORDEHTML_H

#include "Pila.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LectorDeHtml{
private:
    Pila<string>* p = new Pila<string>();
    ifstream archivo;

    void cargarEnPila();

public:
    void set_archivo(const string& nombre);
    Pila<string>* get_pila();
};

#endif
using namespace std;


void LectorDeHtml::set_archivo(const string& nombre) {
    archivo.open(nombre);
    if(archivo.is_open()){
        cargarEnPila();
        archivo.close();
    }else{
        cout << "ERROR! -> El archivo no pudo ser abierto.";
    }

}

Pila<string>* LectorDeHtml::get_pila() {
  std::cout << "Obteniendo pila..." << '\n';
    return p;
}

void LectorDeHtml::cargarEnPila() {
        string lineaDeTexto;
        int error=0;
        string  nodoTexto;
        while(getline(archivo, lineaDeTexto)){  //Se recorren los renglones
            for (int i = 0; (i < lineaDeTexto.length()) && (!error); i++) { //Se recorren los caracteres de los renglones
                nodoTexto = "";

                if (lineaDeTexto.at(i) == '<'){ 

                    for (int x = 0; x < lineaDeTexto.length(); x++) {
                      nodoTexto += lineaDeTexto.at(x);
                      if (lineaDeTexto.at(x)=='>') {
                        x = lineaDeTexto.length()+1;
                      }
                    }

                    std::cout << nodoTexto << '\n';
                    p->apilar(nodoTexto);
                }
            }
        }
}
