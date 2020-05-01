///////// Cabecera de la clase Pila

#ifndef AYED_PROGRAMA_PILA_H
#define AYED_PROGRAMA_PILA_H

#include "Lista.h"

#include <string>
#include <cstdlib>

template <class T> class Pila:public Lista<T>        // Hereda los miembros publicos de la clase Lista
{
public:
    Pila();
    void apilar(T d);
    T tope();
    void desapilar();
    bool pilavacia();
};

#endif
