#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;


//-------------------------------------------------------------------------------------------
//Nodo

template <class T> class Nodo
{
private:
    T dato;
    Nodo* next;

public:
    Nodo();
    Nodo(T a);

    void set_dato(T a);
    void set_next(Nodo* n);
    T get_dato();
    Nodo* get_next();
    bool es_vacio();
};

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

//-------------------------------------------------------------------------------------------
//Lista

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


//-------------------------------------------------------------------------------------------
//Pila

template <class T> class Pila:public Lista<T>        // Hereda los miembros publicos de la clase Lista
{
public:
    Pila();
    void apilar(T d);
    T tope();
    void desapilar();
    bool pilavacia();
};

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


//-------------------------------------------------------------------------------------------
//Lector de HTML

class LectorDeHtml
{
private:
    Pila<string>* p = new Pila<string>();    // Pila de Tokens
    ifstream archivo;
    string token;        // Cadena de texto auxiliar para agregar caracteres al token
    string texto;        // Cadena de texto donde se almacena el texto recibido por la funcion

    void cargarEnPila();
    void leerTexto();

public:
    LectorDeHtml();                       // Constructor
    ~LectorDeHtml();                      // Destructor

    void set_archivo(const string& nombre);
    Pila<string>* get_pila();
};


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

void LectorDeHtml::cargarEnPila() {

   // Descomentar la siguiente linea para ver como trabaja la recursion
   // cout << textoDelArchivo << endl;


    try {      // El metodo erase de la clase string arroja una excepcion que no afecta la modificacion de la cadena pero detiene la ejecucion si no se maneja.

        if (!texto.empty()) {    // Comprueba que la cadena de texto no se haya terminado


            if (texto.at(0) == '<') {

                if (!token.empty())        // Si el proximo caracter es un < y la cadena auxiliar no esta vacia, significa que el token contiene el texto: <p>este texto</p>.
                {
                    p->apilar(token);     // Se carga en la pila el token
                    token = "";           // Se vacia la cadena auxiliar para cargar un nuevo token.
                    cargarEnPila();  // Llamada recursiva.

                }
                else
                {
                    token += texto.at(0);      // Agrego el caracter a la cadena
                    texto.erase(0, 1);     // Eliminamos el caracter que acabamos de agregar a la cadena auxiliar
                    cargarEnPila();
                }
            }

            if ((texto.at(0) != '<') && (texto.at(0) != '>'))
            {
                token += texto.at(0);
                texto.erase(0, 1);
                cargarEnPila();
            }


            if (texto.at(0) == '>')
            {
                token += texto.at(0);      // Se agrega el caracter > y se carga el token en la pila

                p->apilar(token);

                token = "";
                texto.erase(0, 1);
                cargarEnPila();
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
        texto += lineaDeTexto;
    }
    cargarEnPila();
}


//-------------------------------------------------------------------------------------------
//TokenHtml      (Clase Abstracta)

class TagHtml{
public:
    bool tagMostrado;        // Se usa para detectar si el tipo de tag ya ha sido impreso
    string textoDelTag;
    Pila<TagHtml*> *tagsAnidados = new Pila<TagHtml*>();

    virtual void show() = 0;     // Funcion virtual pura
};


//-------------------------------------------------------------------------------------------
//text           Clase del tag <text>

class text : public TagHtml{
public:
    text(string texto){textoDelTag = texto;}
    void show() override;
};

void text::show() {

   if(!textoDelTag.empty()){ cout << "text  " << textoDelTag << endl;}
}


//-------------------------------------------------------------------------------------------
//h1           Clase del tag <h1>

class h1 : public TagHtml{
public:
    h1(string texto){textoDelTag = texto;}
    void show() override;
};

void h1::show() {
    if(!textoDelTag.empty()) cout << "h1     " << endl;
}


//-------------------------------------------------------------------------------------------
//table           Clase del tag <table>

class table : public TagHtml{
public:
    table(){};
    void show() override;
};

void table::show() {

    if(!tagMostrado){
        cout << "table" << endl;
        tagMostrado = true;
    }

   //// funcion recursiva que llama a los metodos show de los tags <tr> en la pila de table
   if(!this->tagsAnidados->pilavacia()){

       tagsAnidados->tope()->show();
       tagsAnidados->desapilar();
       this->show();
   }
}


//-------------------------------------------------------------------------------------------
//tr           Clase del tag <tr>

class tr : public TagHtml{
public:
    tr(){};
    void show() override;
};

void tr::show() {

    if(!tagMostrado){
        cout << "    tr" << endl;
        tagMostrado = true;
    }

    //// funcion recursiva que llama a los metodos show de los tags <th> o <td> en la lista de tr
    if(!tagsAnidados->pilavacia()){

        tagsAnidados->tope()->show();
        tagsAnidados->desapilar();
        this->show();                // Llamada recursiva
    }
}


//-------------------------------------------------------------------------------------------
//th           Clase del tag <th>

class th : public TagHtml{
public:
    th(string texto){textoDelTag = texto;}
    void show() override;
};

void th::show() {

    if(!textoDelTag.empty()){

        cout << "      th " << textoDelTag << endl;
    }
}


//-------------------------------------------------------------------------------------------
//td           Clase del tag <td>

class td : public TagHtml{
public:
    td(string texto){textoDelTag = texto;}
    void show() override;
};

void td::show(){

    if(!textoDelTag.empty()) {

        cout << "      td " << textoDelTag << endl;
    }
}




//-------------------------------------------------------------------------------------------
//Main

void funcioncita(Pila<string> *pilaDeTokens, Pila<TokenHtml*> *pilaDeTags){
    if(!pilaDeTokens->es_vacia()) {
        std::cout << "Me llamaron" << '\n';
        if(pilaDeTokens->tope().at(0) == '<' && pilaDeTokens->tope().at(1) == '/'){       //Detectar tag que cierra
            std::cout << "Detectado tag que cierra: " << pilaDeTokens->tope()  << '\n';

            //Clasificar de que tipo de tag se trata:
                if( pilaDeTokens->tope()=="</table>" ){
                    std::cout << "Detecte una tabla" << '\n';
                    pilaDeTokens->desapilar();
                    pilaDeTags->apilar( new table() );

                    funcioncita(pilaDeTokens, pilaDeTags);

                }
                if(pilaDeTokens->tope()=="</tr>"){
                    std::cout << "Detecte una tr" << '\n';
                    pilaDeTokens->desapilar();
                    pilaDeTags->tope()->tagsAnidados->apilar(new tr());

                    funcioncita(pilaDeTokens, pilaDeTags);

                }
                if(pilaDeTokens->tope()=="</td>"){
                    std::cout << "Detecte una td" << '\n';
                    pilaDeTokens->desapilar();
                    //Se comproba si es texto
                    pilaDeTags->tope()->tagsAnidados->tope()->tagsAnidados->apilar(new td( pilaDeTokens->tope() ));
                    pilaDeTokens->desapilar();      //Se desapila el texto

                    funcioncita(pilaDeTokens, pilaDeTags);
                }

        }else{
            std::cout << "Token no identificado: " <<  pilaDeTokens->tope() << '\n';
            pilaDeTokens->desapilar();
            funcioncita(pilaDeTokens, pilaDeTags);
        }
}
}
string barra(){
    string barra="---------------------------------------------------------";
    return barra;
};
int main() {
    cout << barra() << '\n' << "------------------  Parte 1: Tokenize  ------------------" << '\n' << barra() << endl;
    cout << "Ingrese el nombre del archivo: ";
    string nombre;
    //cin  >> nombre;
    nombre = "archivito.html";

        LectorDeHtml lector;
        lector.set_archivo(nombre);

    std::cout << "Archivo elegido: " << nombre << '\n';

    Pila<string>* pilaDeTokens = lector.get_pila();

    //cout << "Presione Enter para continuar..."; cin.ignore();

    cout << barra() << '\n' << "------------------  Parte 2: Parsing  -------------------" << '\n' << barra() << endl;

        cout << '\n' << "------------------  Parte 2: Parsing  ------------------" << endl;


     Pila<TagHtml*>* pilaDeTags = new Pila<TagHtml*>;  // Puntero a una pila de punteros a objetos TagHtml (Polimorfismo)

    funcioncita(pilaDeTokens, pilaDeTags);

        cout << '\n' << "------------------  Parte 3: Show  ---------------------" << endl;


        while (!pilaDeTags->es_vacia()){

            pilaDeTags->tope()->show();
            pilaDeTags->desapilar();
        }

        return 0;
}
