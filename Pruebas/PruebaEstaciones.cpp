// Prueba de agregar y eliminar estaciones en SistemaBicis.
// Compilar desde la carpeta del proyecto:
#include <iostream>
#include <sstream>
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

template <class Funcion>
static std::string capturarSalida(Funcion funcion) {
    std::ostringstream salida;
    std::streambuf* original = std::cout.rdbuf(salida.rdbuf());
    funcion();
    std::cout.rdbuf(original);
    return salida.str();
}

int main() {
    SistemaBicis sistema;

    // Agregar (el sistema se hace cargo de cada estacion que recibe)
    sistema.agregarEstacion(new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12));
    sistema.agregarEstacion(new Estacion("PAL", "ParqueTresDeFebrero", "Palermo", 40, 35));
    sistema.agregarEstacion(new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4));
    sistema.agregarEstacion(new Estacion("PLZ", "Repetida", "Otro", 10, 5));   // repetida: se rechaza y se libera
    sistema.agregarEstacion(new Estacion("AB", "Corta", "Barrio", 10, 5));     // codigo invalido: idem

    // Si se agregaron bien, se pueden eliminar una vez
    verificar(sistema.eliminarEstacion("PAL"), "PAL se habia agregado y se puede eliminar");
    verificar(!sistema.eliminarEstacion("PAL"), "no se puede eliminar dos veces");
    verificar(!sistema.eliminarEstacion("AB"), "la de codigo invalido no se agrego");
    verificar(!sistema.eliminarEstacion("RET"), "no elimina una estacion que no existe");
    verificar(sistema.eliminarEstacion("PLZ"), "PLZ esta una sola vez (la repetida no entro)");
    verificar(!sistema.eliminarEstacion("PLZ"), "despues de eliminarla PLZ ya no esta");

    std::cout << "\n";
    sistema.mostrarEstadisticasDelHash();   // tiene que quedar 1 estacion (CAB)

    // CAB queda adentro: el destructor de SistemaBicis tiene que liberarla

    std::cout << "\n=== Eliminacion de estacion: bicicletas y viajes ===\n";

    {
        SistemaBicis cascada;
        cascada.agregarEstacion(new Estacion("AAA", "Origen", "Centro", 10, 2));
        cascada.agregarEstacion(new Estacion("BBB", "Destino", "Centro", 10, 1));
        cascada.agregarBicicleta(1, "AAA", "Mecanica", "Averiada", 100);
        cascada.agregarBicicleta(2, "AAA", "Mecanica", "OK", 100);
        cascada.agregarBicicleta(3, "BBB", "Mecanica", "OK", 100);
        cascada.enviarBicicletaAlTaller(1, 2);

        cascada.agregarViaje(new Viaje(1, 2, 111, "AAA", "BBB", 20260101, 10));
        cascada.agregarViaje(new Viaje(2, 3, 222, "BBB", "AAA", 20260102, 10));
        cascada.agregarViaje(new Viaje(3, 3, 111, "BBB", "BBB", 20260103, 10));

        verificar(cascada.eliminarEstacion("AAA"),
                  "una estacion con bicicletas y viajes se puede eliminar");
        verificar(cascada.buscarBicicletaPorId(1) == nullptr
                      && cascada.buscarBicicletaPorId(2) == nullptr,
                  "eliminarEstacion quita del ABB las bicicletas de la estacion");
        verificar(cascada.obtenerCantidadEnTaller() == 0,
                  "eliminarEstacion quita del taller las bicicletas de la estacion");
        verificar(cascada.buscarBicicletaPorId(3) != nullptr,
                  "las bicicletas de otras estaciones se conservan");

        std::string salida = capturarSalida([&cascada]() {
            cascada.mostrarViajesYMinutosDeUsuario(111);
        });
        verificar(salida.find("ID del viaje: 3") != std::string::npos
                      && salida.find("ID del viaje: 1") == std::string::npos,
                  "eliminarEstacion borra los viajes con origen en la estacion");

        salida = capturarSalida([&cascada]() {
            cascada.mostrarViajesYMinutosDeUsuario(222);
        });
        verificar(salida.find("No se encontraron viajes") != std::string::npos,
                  "eliminarEstacion borra los viajes con destino en la estacion");
    }

    std::cout << "\n=== Eliminacion bloqueada por viaje en curso ===\n";

    {
        SistemaBicis enCurso;
        enCurso.agregarEstacion(new Estacion("VIA", "Viaje", "Centro", 5, 1));
        enCurso.agregarBicicleta(10, "VIA", "Mecanica", "OK", 100);
        enCurso.retirarBicicleta("VIA", 123, 20260101);

        bool eliminada = true;
        std::string salida = capturarSalida([&]() {
            eliminada = enCurso.eliminarEstacion("VIA");
        });
        verificar(!eliminada
                      && salida.find("hay un viaje en curso") != std::string::npos,
                  "no se elimina una estacion con un viaje en curso");

        salida = capturarSalida([&]() {
            enCurso.mostrarInformacionDeEstacionPorCodigo("VIA");
        });
        verificar(salida.find("Codigo: VIA") != std::string::npos,
                  "la estacion bloqueada sigue existiendo");
        verificar(enCurso.buscarBicicletaPorId(10) != nullptr,
                  "la bicicleta del viaje en curso sigue existiendo");

        enCurso.devolverBicicleta("VIA", 123, 10, 5);
        verificar(enCurso.eliminarEstacion("VIA"),
                  "al terminar el viaje la estacion se puede eliminar");
        verificar(enCurso.buscarBicicletaPorId(10) == nullptr,
                  "eliminar la estacion quita la bicicleta que estaba en ella");
    }

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}