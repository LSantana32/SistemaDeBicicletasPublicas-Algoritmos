// Pruebas de B.1 (viajes por estacion y rango de fechas),
// B.2 (viajes y minutos por DNI) y B.3 (bicicletas con mas de X km).
// Compilar desde la raiz del proyecto:
//   g++ -std=c++17 -Wall -Wextra Pruebas/PruebaItemB.cpp -o pruebaItemB
#include <iostream>
#include <sstream>
#include <string>

#include "../Sistema/SistemaBicis.h"

static int fallas = 0;

static void verificar(bool condicion, const std::string& descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

template <typename Func>
static std::string capturarSalida(Func funcion) {
    std::ostringstream salida;
    std::streambuf* original = std::cout.rdbuf(salida.rdbuf());
    funcion();
    std::cout.rdbuf(original);
    return salida.str();
}

static int contarOcurrencias(const std::string& texto, const std::string& buscado) {
    int cantidad = 0;
    std::string::size_type posicion = 0;

    while ((posicion = texto.find(buscado, posicion)) != std::string::npos) {
        cantidad++;
        posicion += buscado.length();
    }

    return cantidad;
}

int main() {
    SistemaBicis sistema;

    sistema.agregarEstacion(new Estacion("PLZ", "Plaza", "Centro", 30, 12));
    sistema.agregarEstacion(new Estacion("CAB", "Caballito", "Centro", 25, 4));
    sistema.agregarEstacion(new Estacion("BOE", "Boca", "Sur", 18, 9));

    sistema.agregarViaje(new Viaje(1, 501, 111, "PLZ", "CAB", 20260310, 25));
    sistema.agregarViaje(new Viaje(2, 502, 222, "CAB", "PLZ", 20260311, 40));
    sistema.agregarViaje(new Viaje(3, 503, 111, "PLZ", "CAB", 20260312, 30));
    sistema.agregarViaje(new Viaje(4, 504, 333, "PLZ", "BOE", 20260313, 15));

    std::cout << "=== B.1: viajes por estacion y rango ===\n";

    int cantidad = -1;
    bool ok = sistema.contarViajesDesdeEstacionEnRango(
        "PLZ", 20260310, 20260312, cantidad);
    verificar(ok && cantidad == 2,
              "cuenta los viajes de PLZ en el rango, incluidos los extremos");

    cantidad = -1;
    std::string salida = capturarSalida([&]() {
        ok = sistema.contarViajesDesdeEstacionEnRango(
            "PLZ", 20260313, 20260310, cantidad);
    });
    verificar(!ok && cantidad == 0
                  && salida.find("no puede ser mayor") != std::string::npos,
              "un rango invertido se informa como error");

    cantidad = -1;
    salida = capturarSalida([&]() {
        ok = sistema.contarViajesDesdeEstacionEnRango(
            "ZZZ", 20260310, 20260312, cantidad);
    });
    verificar(!ok && cantidad == 0 && salida.find("no existe") != std::string::npos,
              "una estacion inexistente se informa y no cuenta viajes");

    cantidad = -1;
    ok = sistema.contarViajesDesdeEstacionEnRango(
        "BOE", 20260101, 20261231, cantidad);
    verificar(ok && cantidad == 0, "una estacion sin viajes devuelve 0");

    std::cout << "\n=== B.2: viajes y minutos por DNI ===\n";

    salida = capturarSalida([&]() {
        sistema.mostrarViajesYMinutosDeUsuario(111);
    });
    verificar(salida.find("Total de minutos pedaleados: 55") != std::string::npos,
              "suma los minutos de todos los viajes del DNI");

    salida = capturarSalida([&]() {
        sistema.mostrarViajesYMinutosDeUsuario(999);
    });
    verificar(salida.find("No se encontraron viajes") != std::string::npos,
              "informa cuando el DNI no tiene viajes");

    std::cout << "\n=== B.3: bicicletas con mas de X km ===\n";

    sistema.agregarBicicleta(1, "PLZ", "Mecanica", "OK", 1240);
    sistema.agregarBicicleta(2, "PLZ", "Electrica", "Averiada", 3810);
    sistema.agregarBicicleta(3, "CAB", "Mecanica", "OK", 640);
    sistema.agregarBicicleta(4, "PLZ", "Mecanica", "OK", 1500);

    salida = capturarSalida([&]() {
        sistema.listarBicicletasConMasKm(1000);
    });
    verificar(contarOcurrencias(salida, "ID: ") == 3,
              "lista solo las tres bicicletas con mas de 1000 km");
    verificar(salida.find("ID: 1") != std::string::npos
                  && salida.find("ID: 2") != std::string::npos
                  && salida.find("ID: 4") != std::string::npos
                  && salida.find("ID: 3") == std::string::npos,
              "incluye las bicicletas correctas y excluye la de 640 km");

    salida = capturarSalida([&]() {
        sistema.listarBicicletasConMasKm(1240);
    });
    verificar(contarOcurrencias(salida, "ID: ") == 2,
              "el filtro es estricto: no incluye una bici con exactamente 1240 km");

    salida = capturarSalida([&]() {
        sistema.listarBicicletasConMasKm(10000);
    });
    verificar(salida.find("No hay bicicletas con mas de 10000")
                  != std::string::npos,
              "informa cuando ninguna bicicleta supera el umbral");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
