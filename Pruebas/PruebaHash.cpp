// Pruebas de la tabla hash que indexa las estaciones por codigo (item A.8).
// Verifica insercion, busqueda, eliminacion, colisiones y factor de carga.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaHash.cpp -o pruebaHash
#include <cmath>
#include <iostream>
#include <string>

#include "../Estructuras/TablaHash/TablaHash.h"

static int fallas = 0;

static void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

static bool casiIgual(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

int main() {
    TablaHash<int> tabla(101);
    verificar(tabla.obtenerCantidad() == 0, "una tabla nueva tiene cantidad 0");
    verificar(tabla.obtenerColisiones() == 0, "una tabla nueva no tiene colisiones");
    verificar(casiIgual(tabla.calcularFactorDeCarga(), 0.0), "factor de carga inicial 0");

    verificar(tabla.insertar("PLZ", 1), "se inserta PLZ");
    verificar(tabla.insertar("PAL", 2), "se inserta PAL");
    verificar(tabla.insertar("CAB", 3), "se inserta CAB");
    verificar(tabla.insertar("RET", 4), "se inserta RET");
    verificar(tabla.insertar("CON", 5), "se inserta CON");
    verificar(tabla.insertar("BOE", 6), "se inserta BOE");

    verificar(tabla.obtenerCantidad() == 6, "quedan 6 elementos");
    verificar(tabla.obtenerColisiones() == 0, "los 6 codigos de prueba no colisionan");
    verificar(casiIgual(tabla.calcularFactorDeCarga(), 6.0 / 101.0),
              "factor de carga = 6/101 con los datos de prueba");

    int valor = 0;
    verificar(tabla.buscar("CAB", valor) && valor == 3, "buscar CAB devuelve su valor");
    verificar(!tabla.buscar("ZZZ", valor), "buscar un codigo inexistente devuelve false");
    verificar(!tabla.insertar("PLZ", 99), "no se permite insertar una clave duplicada");
    verificar(tabla.obtenerCantidad() == 6, "el duplicado no cambia la cantidad");

    verificar(tabla.eliminar("PAL"), "eliminar PAL devuelve true");
    verificar(!tabla.buscar("PAL", valor), "PAL ya no se encuentra");
    verificar(!tabla.eliminar("PAL"), "no se puede eliminar dos veces");
    verificar(tabla.obtenerCantidad() == 5, "la cantidad baja a 5");
    verificar(casiIgual(tabla.calcularFactorDeCarga(), 5.0 / 101.0),
              "el factor de carga se recalcula");

    // AAA y AJR comparten cubeta (hash 76): la segunda insercion cuenta como colision.
    TablaHash<int> conColision(101);
    verificar(conColision.insertar("AAA", 10), "se inserta AAA");
    verificar(conColision.insertar("AJR", 20), "se inserta AJR en la misma cubeta");
    verificar(conColision.obtenerCantidad() == 2, "quedan 2 elementos en la cubeta");
    verificar(conColision.obtenerColisiones() == 1, "se registro exactamente 1 colision");
    verificar(conColision.buscar("AAA", valor) && valor == 10,
              "se encuentra AAA pese a la colision");
    verificar(conColision.buscar("AJR", valor) && valor == 20,
              "se encuentra AJR pese a la colision");
    verificar(conColision.eliminar("AAA"), "se elimina AAA de la cubeta con colision");
    verificar(conColision.buscar("AJR", valor) && valor == 20,
              "AJR sigue en la tabla despues de eliminar AAA");
    verificar(!conColision.buscar("AAA", valor), "AAA ya no esta");

    // obtenerTodos recorre todos los elementos vivos.
    TablaHash<int> otra(5);
    otra.insertar("AAA", 1);
    otra.insertar("BBB", 2);
    otra.insertar("CCC", 3);
    int destino[3] = {0, 0, 0};
    otra.obtenerTodos(destino);
    verificar(destino[0] + destino[1] + destino[2] == 6,
              "obtenerTodos devuelve los 3 elementos");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
