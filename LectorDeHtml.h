////////////// Cabecera de la clase LectorDeHtml
/* Esta clase define un objeto que recibe como parametro el nombre de un archivo de html y devuelve una pila donde
 * cada elemento de la misma es una linea del archivo */

#ifndef AYED_PROGRAMA_LECTORDEHTML_H
#define AYED_PROGRAMA_LECTORDEHTML_H

#include "Pila.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LectorDeHtml
{
private:
    Pila<string>* p = new Pila<string>();
    ifstream archivo;

    void cargarEnPila();

public:
    void set_archivo(const string& nombre);
    Pila<string>* get_pila();


};

#endif
