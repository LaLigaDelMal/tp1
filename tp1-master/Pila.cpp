/////////// Implementacion de la clase Pila

#include "Pila.h"


using namespace std;

template <typename T>
Pila<T>::Pila()
{
    Lista<T>();        // Llama al constructor por defecto de la clase Lista
}

template <class T>
void Pila<T>::apilar(T d)
{
    this->add(d);
}

template <class T>
T Pila<T>::tope()
{
    return this->cabeza();
}

template <class T>
void Pila<T>::desapilar()
{
    this->borrar();
}

template <class T>
bool Pila<T>::pilavacia()
{
    return this->es_vacia();
}