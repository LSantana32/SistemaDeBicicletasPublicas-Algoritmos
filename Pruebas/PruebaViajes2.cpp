
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

    SistemaBicis sistema;
    sistema.agregarViaje(viaje1);
    sistema.agregarViaje(viaje2);
    sistema.agregarViaje(viaje3);

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

    return 0;
}
