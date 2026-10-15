#pragma once

#include "SistemaBicis.h"

class Menu {
    private:
        SistemaBicis* sistema;

    public:
        Menu(SistemaBicis* sistema) {
            this->sistema = sistema;
        }

        void iniciarMenu() { }

        void mostrarOpcionesDelMenu() { }

        void procesarOpcionElegida(int opcion) { }
};
