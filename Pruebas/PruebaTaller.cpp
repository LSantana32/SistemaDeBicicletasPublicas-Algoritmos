// Pruebas del taller de reparaciones con min-heap (item B.5).
// Verifica que se extraiga siempre la bicicleta mas urgente y que las
// electricas averiadas entren con prioridad 1.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaTaller.cpp -o pruebaTaller
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
    SistemaBicis sistema;
    sistema.agregarEstacion(new Estacion("TST", "Test", "Centro", 5, 3));
    sistema.agregarBicicleta(1, "TST", "Electrica", "Averiada", 1000);
    sistema.agregarBicicleta(2, "TST", "Mecanica", "Averiada", 2000);
    sistema.agregarBicicleta(4, "TST", "Mecanica", "Averiada", 3000);
    sistema.agregarBicicleta(3, "TST", "Mecanica", "OK", 4000);

    // Se insertan desordenadas. La electrica pide prioridad 3 pero debe forzarse a 1.
    sistema.enviarBicicletaAlTaller(4, 3);
    sistema.enviarBicicletaAlTaller(2, 2);
    sistema.enviarBicicletaAlTaller(1, 3);
    sistema.enviarBicicletaAlTaller(3, 1);   // no esta averiada: no debe entrar
    sistema.enviarBicicletaAlTaller(2, 2);   // duplicada: no debe entrar dos veces
    verificar(sistema.obtenerCantidadEnTaller() == 3,
              "la bicicleta duplicada no se inserta dos veces");

    Bicicleta* electrica = sistema.buscarBicicletaPorId(1);
    Bicicleta* mecanicaMedia = sistema.buscarBicicletaPorId(2);
    Bicicleta* mecanicaBaja = sistema.buscarBicicletaPorId(4);
    Bicicleta* sana = sistema.buscarBicicletaPorId(3);

    sistema.repararSiguienteBicicleta();
    verificar(electrica != nullptr && !electrica->estaAveriada(),
              "se repara primero la electrica (prioridad 1)");
    verificar(mecanicaMedia != nullptr && mecanicaMedia->estaAveriada()
                  && mecanicaBaja != nullptr && mecanicaBaja->estaAveriada(),
              "las mecanicas siguen averiadas tras la primera reparacion");

    sistema.repararSiguienteBicicleta();
    verificar(mecanicaMedia != nullptr && !mecanicaMedia->estaAveriada(),
              "despues se repara la mecanica de prioridad 2");

    sistema.repararSiguienteBicicleta();
    verificar(mecanicaBaja != nullptr && !mecanicaBaja->estaAveriada(),
              "por ultimo se repara la mecanica de prioridad 3");
    verificar(sistema.obtenerCantidadEnTaller() == 0,
              "el taller queda vacio tras reparar todas las bicicletas");

    verificar(sana != nullptr && !sana->estaAveriada(),
              "la bicicleta no averiada nunca cambio de estado");

    sistema.agregarBicicleta(5, "TST", "Mecanica", "Averiada", 5000);
    sistema.enviarBicicletaAlTaller(5, 2);
    sistema.enviarBicicletaAlTaller(5, 2);
    verificar(sistema.obtenerCantidadEnTaller() == 1,
              "la bici 5 queda una sola vez en el taller");

    verificar(sistema.eliminarBicicleta(5),
              "se puede eliminar del arbol una bici que esta en el taller");
    verificar(sistema.obtenerCantidadEnTaller() == 0,
              "al eliminar la bici del arbol tambien sale del taller");
    verificar(sistema.buscarBicicletaPorId(5) == nullptr,
              "la bici eliminada ya no existe en el ABB");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
