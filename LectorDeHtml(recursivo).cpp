#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


//// Interfaz de la clase Nodo
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



//// Interfaz de la clase Lista
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



//// Interfaz de la clase Pila
template <class T> class Pila:public Lista<T>        // Hereda los miembros publicos de la clase Lista
{
public:
    Pila();
    void apilar(T d);
    T tope();
    void desapilar();
    bool pilavacia();
};




//// Interfaz de la clase LectorDeHtml
class LectorDeHtml
{
private:
    Pila<string>* p = new Pila<string>();
    ifstream archivo;


    void cargarEnPila(string texto);
    void leerTexto();

public:
    LectorDeHtml();                       // Constructor
    ~LectorDeHtml();                      // Destructor

    void set_archivo(const string& nombre);
    Pila<string>* get_pila();
};





//// Implementacion de la clase Nodo
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




//// Implementacion de la clase Lista
template <class T>
Lista<T>::Lista()
{
    czo = new Nodo<T>();
}

template <class T>
Lista<T>::Lista(Nodo<T>* n)
{
    czo = n;
}

template <class T>
void Lista<T>::add(T d)
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T>
bool Lista<T>::es_vacia()
{
    return czo->es_vacio();
}

template <class T>
T Lista<T>::cabeza()
{
    if (es_vacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T>
void Lista<T>::borrar() {
    if (!this->es_vacia()) {
        Nodo<T> *tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}





//// Implementacion de la clase Pila
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




//// Implementacion de la clase LectorDeHtml
LectorDeHtml::LectorDeHtml(){}                 // Constructor
LectorDeHtml::~LectorDeHtml()                  // Destructor
{
    delete p;      // Elimina de memoria la pila inicializada
}

void LectorDeHtml::set_archivo(const string& nombre) {

    archivo.open(nombre);

    if(archivo.is_open())
    {
        leerTexto();
        archivo.close();
    }
    else
    {
        cout << "El archivo no pudo ser abierto.";
        exit(1);  // Terminacion del programa por error
    }

}

Pila<string>* LectorDeHtml::get_pila() {

    return p;
}

void LectorDeHtml::cargarEnPila(string textoDelArchivo) {

   // Descomentar la siguiente linea para ver como trabaja la recursion
   // cout << textoDelArchivo << endl;

    static string token;             // Cadena de texto auxiliar para agregar caracteres al token
    static string texto;             // Cadena de texto donde se almacena el texto recibido por la funcion

    texto = textoDelArchivo;

    try {      // El metodo erase de la clase string arroja una excepcion que no afecta la modificacion de la cadena pero detiene la ejecucion si no se maneja.

        if (!texto.empty()) {    // Comprueba que la cadena de texto no se haya terminado


            if (texto.at(0) == '<') {

                if (!token.empty())        // Si el proximo caracter es un < y la cadena auxiliar no esta vacia, significa que el token contiene el texto: <p>este texto</p>.
                {
                    p->apilar(token);     // Se carga en la pila el token
                    token = "";           // Se vacia la cadena auxiliar para cargar un nuevo token.
                    cargarEnPila(texto);  // Llamada recursiva.

                }
                else
                {
                    token += texto.at(0);      // Agrego el caracter a la cadena
                    texto.erase(0, 1);     // Eliminamos el caracter que acabamos de agregar a la cadena auxiliar
                    cargarEnPila(texto);
                }
            }

            if ((texto.at(0) != '<') && (texto.at(0) != '>'))
            {
                token += texto.at(0);
                texto.erase(0, 1);
                cargarEnPila(texto);
            }


            if (texto.at(0) == '>')
            {
                token += texto.at(0);      // Se agrega el caracter > y se carga el token en la pila

                p->apilar(token);

                token = "";
                texto.erase(0, 1);
                cargarEnPila(texto);
            }

        }
    }
    catch (...)     // Los tres puntos ... indican que atrapa cualquier tipo de excepcion
    {

    }
}

void LectorDeHtml::leerTexto() {

    string lineaDeTexto;

    while(!archivo.eof())
    {
        getline(archivo, lineaDeTexto);
        cargarEnPila(lineaDeTexto);
    }

      //  texto de prueba "<p>hola</p><div></div><form>"  -> reemplazar en la llamada a cargarEnPila
}



    int main() {

    LectorDeHtml lector;
    lector.set_archivo("pagina.html");

    // Codigo de prueba para controlar carga de tokens en la pila

    cout << "Nodos de la Pila: " << endl;


    while(!lector.get_pila()->es_vacia())
    {
        cout << lector.get_pila()->tope() << endl;
        lector.get_pila()->desapilar();
    }

    /* Importante:  Si el archivo de texto (.html) tiene saltos de linea se crean nodos vacios
     * o que contienen espacios ("  ") en la Pila.
     * Por lo que cuando se utilize la pila generada por esta clase se deberian chequear estos nodos
     * para no confundirlos con tokens.                                                                */

    return 0;
}
