#pragma once

#include <string>

class Redistribuidor {
    private:
        std::string* codigos;
        int* faltantes;
        int cantidadEstaciones;
        int capacidadCamion;
        bool* elegidas;
        int cantidadSoluciones;

        void probar(int posicion, int sumaActual) { }

        void mostrarSolucion() { }

    public:
        Redistribuidor(std::string* codigos, int* faltantes, int cantidadEstaciones, int capacidadCamion, bool* elegidas, int cantidadSoluciones) {
            this->codigos = codigos;
            this->faltantes = faltantes;
            this->cantidadEstaciones = cantidadEstaciones;
            this->capacidadCamion = capacidadCamion;
            this->elegidas = elegidas;
            this->cantidadSoluciones = cantidadSoluciones;
        }

        int buscarSoluciones() { return 0; }

        ~Redistribuidor() { }
};
