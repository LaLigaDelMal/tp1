/////// Cabecera de la clase Nodo

// Directivas del compilador
#ifndef AYED_PROGRAMA_NODO_H
#define AYED_PROGRAMA_NODO_H

#include <cstdlib>
#include <string>


template <class T> class Nodo
{
private:
    T dato;
    Nodo* next;

public:
    Nodo();         // Constructor por defecto
    Nodo(T a);      // Constructor con parametro generico

    void set_dato(T a);
    void set_next(Nodo* n);

    T get_dato();
    Nodo* get_next();

    bool es_vacio();

};

#endif
