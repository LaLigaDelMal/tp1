#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "LectorDeHtml.h"
#include "LectorDeHtml.cpp"
#include "Nodo.h"
#include "Nodo.cpp"
#include "Lista.h"
#include "Lista.cpp"
#include "Pila.h"
#include "Pila.cpp"

using namespace std;

int main() {
    std::cout << "Inicio" << std::endl;

    LectorDeHtml lector;
    lector.set_archivo("archivito.html");

    Pila<string>* p = new Pila<string>();
    //pila = lector.get_pila();
    //pila->toPrint("caca");

    //TODO Falta imprimir la pila que devuelve el metodo get_pila de la clase LectorDeHtml


    return 1;
}
