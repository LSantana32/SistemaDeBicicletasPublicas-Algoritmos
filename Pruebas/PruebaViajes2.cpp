
#include <iostream>

#include "../Sistema/SistemaBicis.h"

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

    NodoLista<Viaje*>* nodo3 =
        new NodoLista<Viaje*>(viaje3, nullptr);

    NodoLista<Viaje*>* nodo2 =
        new NodoLista<Viaje*>(viaje2, nodo3);

    NodoLista<Viaje*>* nodo1 =
        new NodoLista<Viaje*>(viaje1, nodo2);

    Lista<Viaje*> viajes(nodo1, 3);

    TablaHash<Estacion*> estaciones(nullptr, 10, 0, 0);
    Grafo<std::string> ciclovias(nullptr, 0);
    ABB<int, Bicicleta*> bicicletas(nullptr, 0);
    HeapMin<Bicicleta*> taller(nullptr, 0, 10);

    {
        SistemaBicis sistema(
            estaciones,
            viajes,
            ciclovias,
            bicicletas,
            taller
        );

        std::cout << "=== Viajes del usuario 30123456 ===\n";
        sistema.mostrarViajesYMinutosDeUsuario(30123456);

        std::cout << "\n=== Usuario sin viajes ===\n";
        sistema.mostrarViajesYMinutosDeUsuario(11111111);

        std::cout << "\n=== Viajes desde PLZ entre el 10 y el 12 ===\n";
        std::cout << "Cantidad: "
          << sistema.contarViajesDesdeEstacionEnRango(
                 "PLZ", 20260310, 20260312)
          << '\n';

        std::cout << "\n=== Viajes desde CAB entre el 10 y el 12 ===\n";
        std::cout << "Cantidad: "
          << sistema.contarViajesDesdeEstacionEnRango(
                 "CAB", 20260310, 20260312)
          << '\n';
    }

    delete nodo1;
    delete nodo2;
    delete nodo3;

    delete viaje1;
    delete viaje2;
    delete viaje3;

    return 0;
}
