#include <iostream>
#include "LectorDeHtml.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cerr << "hice un cambio" << '\n';
    LectorDeHtml lector;
    lector.set_archivo("html.txt");

    // Falta imprimir la pila que devuelve el metodo get_pila de la clase LectorDeHtml


    return 0;
}
