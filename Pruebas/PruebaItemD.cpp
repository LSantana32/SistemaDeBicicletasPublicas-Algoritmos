// Pruebas de la redistribucion con backtracking (item D).
// Cubre el ejemplo del enunciado, solucion unica, poda, caso sin solucion,
// reutilizacion del Redistribuidor y validacion de entradas.
// Compilar desde la raiz del proyecto:
//   g++ -std=c++17 -Wall -Wextra Pruebas/PruebaItemD.cpp -o pruebaItemD
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

static int contarCaracter(const std::string& texto, char caracter) {
    int cantidad = 0;
    for (size_t i = 0; i < texto.size(); i++) {
        if (texto[i] == caracter) {
            cantidad++;
        }
    }
    return cantidad;
}

int main() {
    std::cout << "=== Ejemplo del enunciado ===\n";

    SistemaBicis sistema;
    std::string codigos[] = {"PLZ", "CAB", "RET", "CON", "BOE"};
    int faltantes[] = {3, 7, 5, 2, 5};

    std::string salida = capturarSalida([&sistema, &codigos, &faltantes]() {
        sistema.planificarRedistribucion(10, codigos, faltantes, 5);
    });

    verificar(contarCaracter(salida, '{') == 4,
              "se encuentran exactamente cuatro soluciones");
    verificar(salida.find("{ PLZ CAB }") != std::string::npos,
              "se encuentra la solucion { PLZ CAB }");
    verificar(salida.find("{ RET BOE }") != std::string::npos,
              "se encuentra la solucion { RET BOE }");
    verificar(salida.find("{ PLZ RET CON }") != std::string::npos,
              "se encuentra la solucion { PLZ RET CON }");
    verificar(salida.find("{ PLZ CON BOE }") != std::string::npos,
              "se encuentra la solucion { PLZ CON BOE }");
    verificar(salida.find("Cantidad de soluciones: 4") != std::string::npos,
              "se informa la cantidad total de soluciones");

    std::cout << "\n=== Casos borde ===\n";

    std::string codigosUnica[] = {"AAA", "BBB", "CCC"};
    int faltantesUnica[] = {6, 4, 5};
    salida = capturarSalida([&sistema, &codigosUnica, &faltantesUnica]() {
        sistema.planificarRedistribucion(10, codigosUnica, faltantesUnica, 3);
    });
    verificar(contarCaracter(salida, '{') == 1
                  && salida.find("{ AAA BBB }") != std::string::npos,
              "se reconoce una solucion unica");

    salida = capturarSalida([&sistema, &codigos, &faltantes]() {
        sistema.planificarRedistribucion(100, codigos, faltantes, 5);
    });
    verificar(salida.find("No se encontraron soluciones.") != std::string::npos
                  && contarCaracter(salida, '{') == 0,
              "se informa cuando no existe ninguna combinacion");

    std::string codigosPoda[] = {"AAA", "BBB", "CCC", "DDD"};
    int faltantesPoda[] = {6, 5, 4, 3};
    salida = capturarSalida([&sistema, &codigosPoda, &faltantesPoda]() {
        sistema.planificarRedistribucion(10, codigosPoda, faltantesPoda, 4);
    });
    verificar(contarCaracter(salida, '{') == 1
                  && salida.find("{ AAA CCC }") != std::string::npos,
              "la poda descarta las ramas que superan la capacidad");

    std::cout << "\n=== Reutilizacion ===\n";

    Redistribuidor redistribuidor(codigos, faltantes, 5, 10);
    int primeraBusqueda = 0;
    int segundaBusqueda = 0;
    salida = capturarSalida([&redistribuidor, &primeraBusqueda, &segundaBusqueda]() {
        primeraBusqueda = redistribuidor.buscarSoluciones();
        segundaBusqueda = redistribuidor.buscarSoluciones();
    });
    verificar(primeraBusqueda == 4 && segundaBusqueda == 4,
              "buscarSoluciones se puede ejecutar dos veces con el mismo resultado");
    verificar(contarCaracter(salida, '{') == 8,
              "las dos busquedas imprimen las cuatro soluciones cada una");

    std::cout << "\n=== Validacion de entradas ===\n";

    std::string codigosValidos[] = {"PLZ", "CAB"};
    int faltantesValidos[] = {3, 7};

    salida = capturarSalida([&sistema, &codigosValidos, &faltantesValidos]() {
        sistema.planificarRedistribucion(0, codigosValidos, faltantesValidos, 2);
    });
    verificar(salida.find("La capacidad del camion debe ser mayor que 0.")
                  != std::string::npos,
              "se rechaza una capacidad no positiva");

    salida = capturarSalida([&sistema, &codigosValidos, &faltantesValidos]() {
        sistema.planificarRedistribucion(10, codigosValidos, faltantesValidos, 0);
    });
    verificar(salida.find("No hay estaciones para redistribuir.")
                  != std::string::npos,
              "se rechaza una cantidad de estaciones no positiva");

    salida = capturarSalida([&sistema, &faltantesValidos]() {
        sistema.planificarRedistribucion(10, nullptr, faltantesValidos, 2);
    });
    verificar(salida.find("No hay estaciones para redistribuir.")
                  != std::string::npos,
              "se rechaza una lista de codigos nula");

    int faltantesConCero[] = {3, 0};
    salida = capturarSalida([&sistema, &codigosValidos, &faltantesConCero]() {
        sistema.planificarRedistribucion(10, codigosValidos, faltantesConCero, 2);
    });
    verificar(salida.find("Las bicicletas faltantes deben ser mayores que 0.")
                  != std::string::npos,
              "se rechaza una estacion con faltante cero");

    int faltantesNegativos[] = {3, -7};
    salida = capturarSalida([&sistema, &codigosValidos, &faltantesNegativos]() {
        sistema.planificarRedistribucion(10, codigosValidos, faltantesNegativos, 2);
    });
    verificar(salida.find("Las bicicletas faltantes deben ser mayores que 0.")
                  != std::string::npos,
              "se rechaza una estacion con faltante negativo");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
