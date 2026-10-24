
#include "../Sistema/SistemaBicis.h"
#include <iostream>

int main() {
    SistemaBicis sistema;

    std::cout << "\n=== PRUEBA 1: AGREGAR ESTACIONES ===\n";

    sistema.agregarEstacion(
        new Estacion("PLZ", "Plaza de Mayo", "Monserrat", 30, 12)
    );

    sistema.agregarEstacion(
        new Estacion("PAL", "Parque Tres de Febrero", "Palermo", 40, 35)
    );

    sistema.agregarEstacion(
        new Estacion("CAB", "Primera Junta", "Caballito", 25, 4)
    );

    std::cout << "\n=== PRUEBA 2: BUSCAR ESTACION EXISTENTE ===\n";
    sistema.mostrarInformacionDeEstacionPorCodigo("PLZ");

    std::cout << "\n=== PRUEBA 3: BUSCAR ESTACION INEXISTENTE ===\n";
    sistema.mostrarInformacionDeEstacionPorCodigo("XXX");

    std::cout << "\n=== PRUEBA 4: ORDENAR POR CAPACIDAD ===\n";
    sistema.listarEstacionesOrdenadas(1);

    std::cout << "\n=== PRUEBA 5: ORDENAR POR BICICLETAS DISPONIBLES ===\n";
    sistema.listarEstacionesOrdenadas(2);

    std::cout << "\n=== PRUEBA 6: ESTADISTICAS DE LA TABLA HASH ===\n";
    sistema.mostrarEstadisticasDelHash();

    std::cout << "\n=== PRUEBA 7: LISTAR ESTACIONES CON BAJA OCUPACION ===\n";
    sistema.listarEstacionesConBajaOcupacion();

    std::cout << "\n=== PRUEBA 8: ELIMINAR ESTACION EXISTENTE ===\n";
    if (sistema.eliminarEstacion("PAL")) {
        std::cout << "Estacion PAL eliminada correctamente.\n";
    } else {
        std::cout << "No se pudo eliminar la estacion PAL.\n";
    }

    std::cout << "\n=== PRUEBA 9: ELIMINAR ESTACION INEXISTENTE ===\n";
    if (sistema.eliminarEstacion("XXX")) {
        std::cout << "Estacion XXX eliminada correctamente.\n";
    } else {
        std::cout << "No se pudo eliminar la estacion XXX.\n";
    }
    
    std::cout << "\n=== PRUEBA 10: ESTADISTICAS DE LA TABLA HASH DESPUES DE ELIMINAR ===\n";
    sistema.mostrarEstadisticasDelHash();

    std::cout << "\n=== PRUEBA 11: PORCENTAJE DE OCUPACION DE UNA ESTACION ===\n";

    Estacion prueba("TST", "Estacion de prueba", "Centro", 20, 5);

    std::cout << "Porcentaje esperado: 75%\n";
    std::cout << "Porcentaje obtenido: "
            << prueba.calcularPorcentajeOcupacion() << "%\n";

    return 0;
}
