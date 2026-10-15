#pragma once

#include <string>

class Bicicleta {
    private:
        int id;
        std::string codigoEstacion;
        std::string tipo;
        std::string estado;
        int kilometros;

    public:
        Bicicleta(int id, std::string codigoEstacion, std::string tipo, std::string estado, int kilometros) {
            this->id = id;
            this->codigoEstacion = codigoEstacion;
            this->tipo = tipo;
            this->estado = estado;
            this->kilometros = kilometros;
        }

        int getId() { return 0; }

        int getKilometros() { return 0; }

        bool estaAveriada() { return false; }

        bool esElectrica() { return false; }

        void mostrarInformacion() { }
};
