#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstdlib>
#include <sstream>
using namespace std;

//-------------------------------------------------------------------------------------------
//Nodo

template <class T> class Nodo{
private:
    T dato;
    Nodo* next;
public:
    Nodo(){next = NULL;};
    Nodo(T a){dato = a; next = NULL;};
    void set_dato(T a) { dato = a;};
    void set_next(Nodo* n){next = n;};
    T get_dato(){return dato;};
    Nodo* get_next(){return next;};
    bool es_vacio(){return next == NULL;};
};

//-------------------------------------------------------------------------------------------
//Lista


template <class T> class Lista {
private:
    Nodo<T>* czo;
public:
    Lista(){czo = new Nodo<T>();};
    Lista(Nodo<T>* n){ czo = n;};
    void add(T d); //sumar nodos a la lista
    bool esvacia(); //verifica si la lista este vacia
    T cabeza(); //retorna el dato del primer nodo
    void borrar(); //borra la cabeza
    Nodo<T>* getNodo();
};


template <class T> void Lista<T>::add(T d){
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T>bool Lista<T>::esvacia(void){
    return czo->es_vacio();
}

template <class T> T Lista<T>::cabeza(void){
    if (this->esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T> void Lista<T>::borrar() {
    if (!this->esvacia()) {
        Nodo<T> *tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> Nodo<T>* Lista<T>::getNodo() {
    return czo->get_next();
}

//-------------------------------------------------------------------------------------------
//Clase Lector de HTML

template <class T> class Pila:public Lista<T>{
public:
    Pila(){Lista<T>();};
    void apilar(T d){this->add(d);};
    T tope(){return this->cabeza();};
    void desapilar(){this->borrar();};
    bool pilavacia(){return this->esvacia();};
};

//-------------------------------------------------------------------------------------------
//Clase Lector de HTML

class LectorDeHtml{
private:
    ifstream archivo;
    string texto;
    Pila<string> *p = new Pila<string>();
public:
    void set_archivo(); //Carga el archivo html
    void cargarEnPila();
    Pila<string>* get_pila();
};

void LectorDeHtml::set_archivo(){
    archivo.open("archivito.html");
    if(archivo.fail()){
        cout<<"El archivo no pudo ser abierto.";
        exit(1);
    }
}

//CARGA EL ARCHIVO HTML EN UNA PILA
void LectorDeHtml::cargarEnPila(){
    string lineaDeTexto; //Almacena cada linea del texto
    string nodoTexto;    //Almacena cada tag o texto para almacenarlo en la pila
    while(!archivo.eof()){
        getline(archivo,lineaDeTexto);
        for(int i=0; i<lineaDeTexto.length(); i++){
            //GUARDA LOS TAGS
            if(lineaDeTexto.at(i)=='<'){
                int aux = i;
                while(lineaDeTexto.at(aux)!='>'){
                    nodoTexto += lineaDeTexto.at(aux);
                    aux++;
                }
                nodoTexto += lineaDeTexto.at(aux);
                p->apilar(nodoTexto);
                //cout<<nodoTexto<<endl;
                nodoTexto = "";
            }
            //GUARDA EL TEXTO
            if((i+1)!=lineaDeTexto.length()){  //Se asegura que lineaDeTexto no termino
                if ((lineaDeTexto.at(i)=='>')){
                    int aux = i+1;
                    while(lineaDeTexto.at(aux)!='<'){
                        nodoTexto +=lineaDeTexto.at(aux);
                        aux++;
                    }
                    p->apilar(nodoTexto);
                    //cout<<nodoTexto<<endl;
                    nodoTexto = "";
                }
            }
        }
    }
}

Pila<string>* LectorDeHtml::get_pila() {
    return p;
}

//-------------------------------------------------------------------------------------------
//Clase abstracta para crear Tokens

template <class T> class TokenHTML{
public:
    string tipoToken;      //ej: "<text>", "<tr>"
    Lista<T> *tagsAnidados = new Lista<T>();
    //ej: tags dentro de "<table>" seran "<tr>", entonces tagsAnidados sera una lista de "<tr>"
    //lo mismo para el contenido de "<text>" o "<th>"

    TokenHTML(string token){tipoToken=token;};
    virtual void show();
    void addTagAnidado(T tag);
};

template <class T> void TokenHTML<T>::show(){
    //recorrer Lista y ejecutar sus metodos show();
    std::cout << tagsAnidados->cabeza() << '\n';
};

template <class T> void TokenHTML<T>::addTagAnidado(T tag){
    tagsAnidados->add(tag);
    //cout << "Se aniadio '"<< nodo << "' al token " << tipoToken<< endl;
};

//------------------------------------------------------------------------------------------------
//Clases de Tokens

template <class T> class TK_text : public TokenHTML<T>{
public:
    TK_text(string token):TokenHTML<T>(token){};
    //Hereda y ejecuta automaticamente el constructor de TokenHTML
};

template <class T> class TK_tr : public TokenHTML<T>{
public:
    TK_tr(string token):TokenHTML<T>(token){};
};

template <class T> class TK_td : public TokenHTML<T>{
public:
    TK_td(string token):TokenHTML<T>(token){};
};

//-------------------------------------------------------------------------------------------
//Main

string barra(){
    string barra="---------------------------------------------------------";
    return barra;
};

int main(){
    cout << barra() << '\n' << "------------------  Parte 1: Tokenize  ------------------" << '\n' << barra() << endl;

    std::cout << "Tokenizandoooooo" << '\n'; //borrar antes de mandar
    LectorDeHtml lector;
    lector.set_archivo();
    lector.cargarEnPila();


    cout << barra() << '\n' << "------------------  Parte 2: Parsing  -------------------" << '\n' << barra() << endl;

    string ultimoNodo;
    bool salir1 = true;
    while(salir1){
        Pila<string>* pilaDeLectura = lector.get_pila();
        bool salir = true;
        while (salir) {
                pilaDeLectura->desapilar();
                std::cout << pilaDeLectura->tope() << '\n';
                if(pilaDeLectura->tope().empty()){
                    std::cout << "Todo bien" << '\n';
                    //ultimoNodo = pilaDeLectura->tope();
                    salir=false;
                }else{
                }
        }
        salir1=false;
    }

    // TK_td<string> *td = new TK_td<string>("<td>");
    // td->addTagAnidado("Soy un td");
    // td->show();
    //
    // TK_tr<TK_td> *tr = new TK_tr<TK_td>("<tr>");
    // //tr->addTagAnidado(td);
    // //tr->show();


    cout << barra() << '\n' << "--------------------  Parte 3: Show  --------------------" << '\n' << barra() << endl;

    //delete td;
    //delete tr;
    return 1;
};
