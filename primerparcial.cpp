#include <iostream>
#include <fstream>

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

//-------------------------------------------------------------------------------------------
//Clase Lector de HTML

template <class T> class Pila:public Lista<T>{
public:
    Pila(){Lista<T>();};
    void apilar(T d){this->add(d);};
    T tope(void){return this->cabeza();};
    void desapilar(void){this->borrar();};
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

//-------------------------------------------------------------------------------------------
//Clase abstracta para crear Tokens

class TokenHTML{
public:
    string tipoToken;      //ej: "<text>", "<tr>"
    Lista<string> *tagsAnidados;
    //ej: tags dentro de "<table>" seran "<tr>", entonces tagsAnidados sera una lista de "<tr>"
    //lo mismo para el contenido de "<text>" o "<th>"

    TokenHTML(string token){tipoToken=token;};  //TODO ver si se pasa un Nodo por argumentos
    virtual void show(){
        //recorrer Lista y ejecutar sus metodos show();
        std::cout << tipoToken << '\n';
    };
    void addC(string sr){
        tagsAnidados->add(sr);
        cout << "Se añadio '"<< sr << "' al token " << tipoToken<< '\n';
    }
};

class TK_text : public TokenHTML{
public:
    TK_text(string token):TokenHTML(token){};
    //Hereda y ejecuta automaticamente el constructor de TokenHTML
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
    TK_text *tabla = new TK_text("<tabla>");
    tabla->show();
    //tabla->addC("<tr>");


    cout << barra() << '\n' << "--------------------  Parte 3: Show  --------------------" << '\n' << barra() << endl;

    delete tabla;
    return 1;
};
