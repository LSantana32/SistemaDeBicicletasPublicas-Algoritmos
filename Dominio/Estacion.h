#pragma once

#include <string>

#include "../Estructuras/Cola/Cola.h"

class Estacion {
    private:
        std::string codigo;
        std::string nombre;
        std::string barrio;
        int capacidadAnclajes;
        int bicisDisponibles;
        Cola<int> colaEspera;

    public:
        Estacion(std::string codigo, std::string nombre, std::string barrio, int capacidadAnclajes, int bicisDisponibles, Cola<int> colaEspera)
            : colaEspera(colaEspera) {
            this->codigo = codigo;
            this->nombre = nombre;
            this->barrio = barrio;
            this->capacidadAnclajes = capacidadAnclajes;
            this->bicisDisponibles = bicisDisponibles;
        }

        std::string getCodigo() { return std::string(); }

        double calcularPorcentajeOcupacion() { return 0.0; }

        bool retirarBicicleta(int dni) { return false; }

        int devolverBicicleta() { return 0; }

        void mostrarInformacion() { }
};
