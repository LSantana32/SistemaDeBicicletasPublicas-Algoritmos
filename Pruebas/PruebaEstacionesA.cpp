// Pruebas de integracion de los metodos del item A que solo imprimen:
// A.1 consultar estacion, A.4 listar ordenadas, A.5 baja ocupacion y A.8 hash.
// Se captura std::cout para poder hacer aserciones sobre la salida.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaEstacionesA.cpp -o pruebaEstacionesA
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

static bool contiene(const std::string& texto, const std::string& buscado) {
    return texto.find(buscado) != std::string::npos;
}

template <class F>
static std::string capturarSalida(F accion) {
    std::ostringstream salida;
    std::streambuf* original = std::cout.rdbuf(salida.rdbuf());
    accion();
    std::cout.rdbuf(original);
    return salida.str();
}

static bool aparecenEnOrden(const std::string& texto,
                            const std::string* codigos, int cantidad) {
    size_t anterior = 0;

    for (int i = 0; i < cantidad; i++) {
        size_t posicion = texto.find("Codigo: " + codigos[i]);
        if (posicion == std::string::npos) {
            return false;
        }
        if (i > 0 && posicion <= anterior) {
            return false;
        }
        anterior = posicion;
    }

    return true;
}

int main() {
    std::cout << "=== A.1 consultar estacion ===\n";
    {
        SistemaBicis sistema;
        sistema.agregarEstacion(new Estacion("AAA", "Plaza", "Centro", 10, 5));

        std::string salida = capturarSalida([&] {
            sistema.mostrarInformacionDeEstacionPorCodigo("AAA");
        });
        verificar(contiene(salida, "Codigo: AAA"), "muestra el codigo");
        verificar(contiene(salida, "Nombre: Plaza"), "muestra el nombre");
        verificar(contiene(salida, "Barrio: Centro"), "muestra el barrio");
        verificar(contiene(salida, "Capacidad de anclajes: 10"), "muestra la capacidad");
        verificar(contiene(salida, "Bicis disponibles: 5"), "muestra las bicis disponibles");

        salida = capturarSalida([&] {
            sistema.mostrarInformacionDeEstacionPorCodigo("ZZZ");
        });
        verificar(contiene(salida, "no encontrada"), "avisa cuando el codigo no existe");
    }

    std::cout << "\n=== A.4 listar estaciones ordenadas ===\n";
    {
        SistemaBicis sistema;
        sistema.agregarEstacion(new Estacion("AAA", "A", "B", 10, 5));
        sistema.agregarEstacion(new Estacion("BBB", "B", "B", 20, 1));
        sistema.agregarEstacion(new Estacion("CCC", "C", "B", 30, 9));
        sistema.agregarEstacion(new Estacion("DDD", "D", "B", 40, 2));

        std::string salida = capturarSalida([&] {
            sistema.listarEstacionesOrdenadas(1);
        });
        const std::string porCapacidad[4] = {"AAA", "BBB", "CCC", "DDD"};
        verificar(aparecenEnOrden(salida, porCapacidad, 4),
                  "orden ascendente por capacidad de anclajes");

        salida = capturarSalida([&] {
            sistema.listarEstacionesOrdenadas(2);
        });
        const std::string porBicis[4] = {"BBB", "DDD", "AAA", "CCC"};
        verificar(aparecenEnOrden(salida, porBicis, 4),
                  "orden ascendente por bicicletas disponibles");
    }

    std::cout << "\n=== A.5 estaciones con baja ocupacion ===\n";
    {
        SistemaBicis sistema;
        sistema.agregarEstacion(new Estacion("AAA", "A", "B", 100, 0));   // 0 %
        sistema.agregarEstacion(new Estacion("BBB", "B", "B", 100, 19));  // 19 %
        sistema.agregarEstacion(new Estacion("CCC", "C", "B", 100, 20));  // 20 % no entra
        sistema.agregarEstacion(new Estacion("DDD", "D", "B", 100, 21));  // 21 % no entra

        std::string salida = capturarSalida([&] {
            sistema.listarEstacionesConBajaOcupacion();
        });
        verificar(contiene(salida, "Codigo: AAA") && contiene(salida, "Codigo: BBB"),
                  "lista las estaciones con menos del 20 %");
        verificar(!contiene(salida, "Codigo: CCC") && !contiene(salida, "Codigo: DDD"),
                  "excluye las estaciones con 20 % o mas");
    }
    {
        SistemaBicis sistema;
        sistema.agregarEstacion(new Estacion("EEE", "E", "B", 100, 20));

        std::string salida = capturarSalida([&] {
            sistema.listarEstacionesConBajaOcupacion();
        });
        verificar(contiene(salida, "No hay estaciones con baja ocupacion"),
                  "avisa cuando ninguna estacion tiene baja ocupacion");
    }

    std::cout << "\n=== A.8 estadisticas de la tabla hash ===\n";
    {
        SistemaBicis sistema;
        sistema.agregarEstacion(new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12));
        sistema.agregarEstacion(new Estacion("PAL", "ParqueTresDeFebrero", "Palermo", 40, 35));
        sistema.agregarEstacion(new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4));
        sistema.agregarEstacion(new Estacion("RET", "Retiro", "Retiro", 20, 8));
        sistema.agregarEstacion(new Estacion("CON", "Congreso", "Monserrat", 15, 3));
        sistema.agregarEstacion(new Estacion("BOE", "Boca", "Boca", 18, 9));

        std::string salida = capturarSalida([&] {
            sistema.mostrarEstadisticasDelHash();
        });
        verificar(contiene(salida, "Estaciones en la tabla: 6"),
                  "informa que hay 6 estaciones");
        verificar(contiene(salida, "Colisiones: 0"),
                  "informa 0 colisiones con los datos de prueba");
        verificar(contiene(salida, "Factor de carga: 0.059"),
                  "informa un factor de carga de 6/101");
    }

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
