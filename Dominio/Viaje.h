#pragma once

#include <string>
#include <iostream>

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

        int getFecha() { return fecha; }

        int getDniUsuario() { return dniUsuario; }

        std::string getEstacionOrigen() { return estacionOrigen; }

        int getDuracionMin() { return duracionMin; }

        void mostrarInformacion() { 
            std::cout << "ID del viaje: " << id << '\n';
            std::cout << "ID de bicicleta: " << idBici << '\n';
            std::cout << "DNI del usuario: " << dniUsuario << '\n';
            std::cout << "Estacion de origen: " << estacionOrigen << '\n';
            std::cout << "Estacion de destino: " << estacionDestino << '\n';
            std::cout << "Fecha: " << fecha << '\n';
            std::cout << "Duracion: " << duracionMin << " minutos\n";
        }
};
