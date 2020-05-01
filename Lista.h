///////// Cabecera de la clase Lista

#ifndef AYED_PROGRAMA_LISTA_H
#define AYED_PROGRAMA_LISTA_H

#include "Nodo.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T> class Lista
{
private:
    Nodo<T>* czo;

public:
    Lista();
    Lista(Nodo<T>* n);
    void add(T d);
    bool es_vacia();
    T cabeza();
    void borrar();     // Borra el Nodo cabeza
};

#endif
