///////// Implementacion de la clase Lista

#include "Lista.h"

using namespace std;

template <class T> Lista<T>::Lista() {
    czo = new Nodo<T>();
}

template <class T> Lista<T>::Lista(Nodo<T>* n) {
    czo = n;
}

template <class T> void Lista<T>::add(T d) {
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T> bool Lista<T>::es_vacia() {
    return czo->es_vacio();
}

template <class T> T Lista<T>::cabeza() {
    if (es_vacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T> void Lista<T>::borrar() {
    if (!this->es_vacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}
