// Pruebas del porcentaje de ocupacion de una estacion (item A.5).
// La ocupacion es bicisDisponibles / capacidadAnclajes.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaEstacion.cpp -o pruebaEstacion
#include <cmath>
#include <iostream>
#include <string>

#include "../Dominio/Estacion.h"

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
    Estacion veinticinco("AAA", "A", "B", 20, 5);
    verificar(casiIgual(veinticinco.calcularPorcentajeOcupacion(), 25.0),
              "5 de 20 bicis = 25 %");

    Estacion llena("BBB", "B", "B", 100, 100);
    verificar(casiIgual(llena.calcularPorcentajeOcupacion(), 100.0),
              "100 de 100 bicis = 100 %");

    Estacion vacia("CCC", "C", "B", 100, 0);
    verificar(casiIgual(vacia.calcularPorcentajeOcupacion(), 0.0),
              "0 de 100 bicis = 0 %");

    Estacion sinCapacidad("DDD", "D", "B", 0, 0);
    verificar(casiIgual(sinCapacidad.calcularPorcentajeOcupacion(), 0.0),
              "capacidad 0 devuelve 0 % sin dividir por cero");

    Estacion diecinueve("EEE", "E", "B", 100, 19);
    verificar(casiIgual(diecinueve.calcularPorcentajeOcupacion(), 19.0),
              "19 de 100 bicis = 19 %");

    Estacion veinte("FFF", "F", "B", 100, 20);
    verificar(casiIgual(veinte.calcularPorcentajeOcupacion(), 20.0),
              "20 de 100 bicis = 20 %");

    Estacion veintiuno("GGG", "G", "B", 100, 21);
    verificar(casiIgual(veintiuno.calcularPorcentajeOcupacion(), 21.0),
              "21 de 100 bicis = 21 %");

    Estacion fraccion("HHH", "H", "B", 15, 3);
    verificar(casiIgual(fraccion.calcularPorcentajeOcupacion(), 20.0),
              "3 de 15 bicis = 20 %");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
