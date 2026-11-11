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

        void mostrarSolucion() {
            std::cout << "{ ";

            for (int i = 0; i < cantidadEstaciones; i++) {
                if (elegidas[i]) {
                    std::cout << codigos[i] << " ";
                }
            }

            std::cout << "}" << std::endl;
        }

        void probar(int posicion, int sumaActual) {

        // Caso 1: encontramos una solucion
            if (sumaActual == capacidadCamion) {
                mostrarSolucion();
                cantidadSoluciones++;
                return;
            }

        // Caso 2: superamos la capacidad o ya no quedan estaciones para evaluar
            if (sumaActual > capacidadCamion ||
                posicion >= cantidadEstaciones) {
                return;
            }

        // Opcion 1: incluir la estacion actual
            elegidas[posicion] = true;

            probar(
                posicion + 1,
                sumaActual + faltantes[posicion]
            );

        // Backtracking: deshacer la eleccion
            elegidas[posicion] = false;

        // Opcion 2: no incluir la estacion actual
            probar(posicion + 1, sumaActual);
        }

    public:
        Redistribuidor(std::string* codigos, int* faltantes,
             int cantidadEstaciones, int capacidadCamion) {

            this->codigos = codigos;
            this->faltantes = faltantes;
            this->cantidadEstaciones = cantidadEstaciones;
            this->capacidadCamion = capacidadCamion;

            elegidas = new bool[cantidadEstaciones];

            for (int i = 0; i < cantidadEstaciones; i++) {
                elegidas[i] = false;
            }

            cantidadSoluciones = 0;
            }
        
            int buscarSoluciones() { 
                cantidadSoluciones = 0;

                probar(0, 0);

                return cantidadSoluciones;
            }
            
            ~Redistribuidor() { delete[] elegidas; }
        };

        inline void planificarRedistribucion(int capacidadCamion, std::string* codigos,
             int* faltantes, int cantidad) 
        {
            Redistribuidor redistribuidor(
                codigos, faltantes,
                cantidad, capacidadCamion);

            int soluciones = redistribuidor.buscarSoluciones();

            if (soluciones == 0) {
                std::cout << "No se encontraron soluciones." << std::endl;
            } else {
                std::cout << "Cantidad de soluciones: "
                  << soluciones << std::endl;
            }    
        };
