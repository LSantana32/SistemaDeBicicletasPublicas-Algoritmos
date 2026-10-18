#pragma once

#include <string>
#include <iostream>

#include "../Estructuras/Cola/Cola.h"

class Estacion
{
private:
    std::string codigo;
    std::string nombre;
    std::string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;
    Cola<int> colaEspera;

public:
// Cada estacion inicializa su propia cola de espera vacia.
// No se recibe una Cola por parametro porque la clase Cola no permite copias.
//Osea que borre el parametro porque se rompia todo, basicamente.
    Estacion(std::string codigo, std::string nombre, std::string barrio, int capacidadAnclajes, int bicisDisponibles, Cola<int> colaEspera)
        : colaEspera()
    {
        this->codigo = codigo;
        this->nombre = nombre;
        this->barrio = barrio;
        this->capacidadAnclajes = capacidadAnclajes;
        this->bicisDisponibles = bicisDisponibles;
    }

    std::string getCodigo() { return codigo; }

    int getCapacidadAnclajes() { 
        return capacidadAnclajes;
    }
    double calcularPorcentajeOcupacion() { 
        if(capacidadAnclajes == 0){
            return 0.0;
        }

        int ocupacion = capacidadAnclajes - bicisDisponibles;
        double porcentaje = (ocupacion * 100) / capacidadAnclajes;
        
        return porcentaje; 
        }

    int getBicisDisponibles() { return bicisDisponibles; }

    double calcularPorcentajeOcupacion() { return 0.0; }

    bool retirarBicicleta(int dni) { return false; }

    int devolverBicicleta() { return 0; }

    void mostrarInformacion()
    {
        std::cout << "Codigo: " << codigo << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Barrio: " << barrio << std::endl;
        std::cout << "Capacidad de anclajes: " << capacidadAnclajes << std::endl;
        std::cout << "Bicis disponibles: " << bicisDisponibles << std::endl;
    }
};
