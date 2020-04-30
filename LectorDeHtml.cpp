//////////// Implementacion de la clase LectorDeHtml

#include "LectorDeHtml.h"

using namespace std;


void LectorDeHtml::set_archivo(const string& nombre) {

    archivo.open(nombre);

    if(archivo.is_open())
    {
        cargarEnPila();
        archivo.close();
    }
    else
    {
        cout << "ERROR! -> El archivo no pudo ser abierto.";
    }

}

Pila<string>* LectorDeHtml::get_pila() {

    return p;
}

void LectorDeHtml::cargarEnPila() {

        string lineaDeTexto;

        while(getline(archivo, lineaDeTexto))
        {
            p->apilar(lineaDeTexto);
        }

}