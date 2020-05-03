#include <iostream>
#include <fstream>

#include <cstdlib>
#include <sstream>
using namespace std;


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
template <class T> class Pila:public Lista<T>{
public:
    Pila(){Lista<T>();};
    void apilar(T d){this->add(d);};
    T tope(void){return this->cabeza();};
    void desapilar(void){this->borrar();};
    bool pilavacia(){return this->esvacia();};
};


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
	archivo.open("archivo.html");
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
        cout<<nodoTexto<<endl;
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
		    cout<<nodoTexto<<endl;
	     	nodoTexto = "";
		    }
	    }
    }
    }
}

int main (){

	LectorDeHtml lector;
	lector.set_archivo();
	lector.cargarEnPila();

	return 0;
}
