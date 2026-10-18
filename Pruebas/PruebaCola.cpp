// Prueba de Cola<T> sola, sin ninguna clase del sistema.
#include <iostream>
#include <string>
#include "../Estructuras/Cola/Cola.h"

int fallas = 0;

void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

int main() {
    Cola<int> cola;
    verificar(cola.estaVacia(), "una cola nueva esta vacia");

    cola.encolar(1);
    cola.encolar(2);
    cola.encolar(3);
    verificar(cola.obtenerLargo() == 3, "despues de 3 encolar el largo es 3");
    verificar(cola.verPrimero() == 1, "verPrimero devuelve el primero que entro");
    verificar(cola.desencolar() == 1, "desencolar respeta el orden (1)");
    verificar(cola.desencolar() == 2, "desencolar respeta el orden (2)");
    verificar(cola.desencolar() == 3, "desencolar respeta el orden (3)");
    verificar(cola.estaVacia(), "queda vacia");

    // Si desencolar no pone ultimo en nullptr al vaciarse, esto falla
    cola.encolar(7);
    verificar(cola.verPrimero() == 7, "se puede volver a usar despues de vaciarla");

    // Funciona con otros tipos (por ejemplo, la usara el BFS con punteros)
    Cola<std::string> codigos;
    codigos.encolar("PLZ");
    codigos.encolar("CAB");
    verificar(codigos.desencolar() == "PLZ", "funciona con string");

    // Queda con elementos adentro: el destructor tiene que liberarlos

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}