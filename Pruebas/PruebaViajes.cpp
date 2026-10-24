
#include <iostream>

#include "../Dominio/Viaje.h"
#include "../Estructuras/Lista/NodoLista.h"
#include "../Estructuras/Lista/Lista.h"

int main() {
    Viaje* viaje1 = new Viaje(
        9001, 501, 30123456, "PLZ", "PAL", 20260310, 25
    );

    Viaje* viaje2 = new Viaje(
        9002, 502, 27654321, "PAL", "CAB", 20260311, 40
    );

    Viaje* viaje3 = new Viaje(
        9003, 503, 30123456, "CAB", "PLZ", 20260312, 15
    );

    NodoLista<Viaje*>* nodo3 = new NodoLista<Viaje*>(viaje3, nullptr);
    NodoLista<Viaje*>* nodo2 = new NodoLista<Viaje*>(viaje2, nodo3);
    NodoLista<Viaje*>* nodo1 = new NodoLista<Viaje*>(viaje1, nodo2);

    Lista<Viaje*> viajes(nodo1, 3);

    NodoLista<Viaje*>* actual = viajes.obtenerPrimero();
    int dniBuscado = 30123456;
    int totalMinutos = 0;

    while (actual != nullptr) {
        Viaje* viaje = actual->getDato();

        if (viaje->getDniUsuario() == dniBuscado) {
            viaje->mostrarInformacion();
            totalMinutos += viaje->getDuracionMin();
        }

        actual = actual->getSiguiente();
    }

    std::cout << "Total de minutos: " << totalMinutos << '\n';

    delete viaje1;
    delete viaje2;
    delete viaje3;

    return 0;
}
