#pragma once

#include <iostream>
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

        int getId() { return id; }

        int getKilometros() { return kilometros; }

        bool estaAveriada() { return estado == "Averiada"; }

        bool esElectrica() { return tipo == "Electrica"; }

        void mostrarInformacion() { 
            std::cout << "ID: " << id << std::endl;
            std::cout << "Estacion: " << codigoEstacion << std::endl;
            std::cout << "Tipo: " << tipo << std::endl;
            std::cout << "Estado: " << estado << std::endl;
            std::cout << "Kilometros: " << kilometros << std::endl;
        }
};
