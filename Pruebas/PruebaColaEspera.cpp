// Pruebas de la cola de espera por estacion (item B.4).
// Incluye pruebas unitarias de Estacion y una prueba de integracion con SistemaBicis.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaColaEspera.cpp -o pruebaColaEspera
#include <iostream>
#include <string>

#include "../Sistema/SistemaBicis.h"

static int fallas = 0;

static void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

int main() {
    std::cout << "=== Unidad: Estacion ===\n";

    Estacion conBicis("AAA", "Con bicis", "Centro", 5, 2);
    verificar(conBicis.retirarBicicleta(100), "retirar con bicis devuelve true");
    verificar(conBicis.getBicisDisponibles() == 1, "retirar descuenta una bici");

    Estacion vacia("BBB", "Vacia", "Centro", 5, 0);
    verificar(!vacia.retirarBicicleta(100), "sin bicis, retirar encola y devuelve false");
    verificar(!vacia.retirarBicicleta(200), "se encola un segundo usuario");
    verificar(vacia.getBicisDisponibles() == 0, "encolar no modifica las bicis disponibles");
    verificar(vacia.devolverBicicleta() == 100, "devolver asigna al primero de la cola (FIFO)");
    verificar(vacia.devolverBicicleta() == 200, "devolver asigna al siguiente de la cola");
    verificar(vacia.devolverBicicleta() == -1, "sin usuarios en espera, devolver suma una bici");
    verificar(vacia.getBicisDisponibles() == 1, "la devolucion incremento las bicis disponibles");

    Estacion llena("CCC", "Llena", "Centro", 1, 1);
    verificar(llena.devolverBicicleta() == -2, "devolver en estacion llena devuelve -2");
    verificar(llena.getBicisDisponibles() == 1, "la estacion llena no cambia su cantidad");

    std::cout << "\n=== Integracion: SistemaBicis ===\n";

    SistemaBicis sistema;
    sistema.agregarEstacion(new Estacion("TST", "Test", "Centro", 5, 1));
    sistema.agregarBicicleta(10, "TST", "Mecanica", "OK", 100);

    Bicicleta* bici = sistema.buscarBicicletaPorId(10);
    verificar(bici != nullptr && bici->getCodigoEstacion() == "TST", "la bici arranca en la estacion");

    // 111 retira la unica bici y luego 222 queda en espera.
    sistema.retirarBicicleta("TST", 111, 20260101);
    verificar(bici != nullptr && bici->getCodigoEstacion() == "", "la bici retirada queda en uso");

    sistema.retirarBicicleta("TST", 222, 20260101);

    // 111 devuelve la bici: debe asignarse al usuario 222 que estaba esperando.
    sistema.devolverBicicleta("TST", 111, 10);
    verificar(bici != nullptr && bici->getCodigoEstacion() == "",
              "la bici devuelta se asigna al usuario en espera y sigue en uso");

    // 222 devuelve la bici: ahora si queda disponible en la estacion.
    sistema.devolverBicicleta("TST", 222, 10);
    verificar(bici != nullptr && bici->getCodigoEstacion() == "TST",
              "sin usuarios en espera, la bici queda en la estacion");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
