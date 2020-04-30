/////// Implementacion de la clase Nodo

#include "Nodo.h"

using namespace std;

template <class T>
Nodo<T>::Nodo()
{
    next = NULL;
}

template <class T>
Nodo<T>::Nodo(T a)
{
    dato = a;
    next = NULL;
}

template <class T>
void Nodo<T>::set_dato(T a)
{
    dato = a;
}

template <class T>
void Nodo<T>::set_next(Nodo* n)
{
    next = n;
}

template <class T>
T Nodo<T>::get_dato()
{
    return dato;
}

template <class T>
Nodo<T>* Nodo<T>::get_next()
{
    return next;
}

template <class T>
bool Nodo<T>::es_vacio()
{
    return next == NULL;
}
