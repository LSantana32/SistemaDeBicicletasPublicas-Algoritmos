#pragma once

#include <string>

class Viaje {
    private:
        int id;
        int idBici;
        int dniUsuario;
        std::string estacionOrigen;
        std::string estacionDestino;
        int fecha;
        int duracionMin;

    public:
        Viaje(int id, int idBici, int dniUsuario, std::string estacionOrigen, std::string estacionDestino, int fecha, int duracionMin) {
            this->id = id;
            this->idBici = idBici;
            this->dniUsuario = dniUsuario;
            this->estacionOrigen = estacionOrigen;
            this->estacionDestino = estacionDestino;
            this->fecha = fecha;
            this->duracionMin = duracionMin;
        }

        int getFecha() { return 0; }

        int getDniUsuario() { return 0; }

        std::string getEstacionOrigen() { return std::string(); }

        int getDuracionMin() { return 0; }

        void mostrarInformacion() { }
};
