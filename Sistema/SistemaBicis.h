#pragma once

#include <string>
#include <iostream>

#include "../Estructuras/TablaHash/TablaHash.h"
#include "../Estructuras/Lista/Lista.h"
#include "../Estructuras/Grafo/Grafo.h"
#include "../Estructuras/ABB/ABB.h"
#include "../Estructuras/HeapMin/HeapMin.h"
#include "../Estructuras/Redistribuidor/Redistribuidor.h"
#include "../Dominio/Estacion.h"
#include "../Dominio/Bicicleta.h"
#include "../Dominio/Viaje.h"

class SistemaBicis {
    private:
        TablaHash<Estacion*> estaciones;
        Lista<Viaje*> viajes;
        Grafo<std::string> ciclovias;
        ABB<int, Bicicleta*> bicicletas;
        HeapMin<Bicicleta*> taller;

    public:
        SistemaBicis(TablaHash<Estacion*> estaciones, Lista<Viaje*> viajes, Grafo<std::string> ciclovias, ABB<int, Bicicleta*> bicicletas, HeapMin<Bicicleta*> taller)
            : estaciones(estaciones), viajes(viajes), ciclovias(ciclovias), bicicletas(bicicletas), taller(taller) {
        }

        void cargarDatosDesdeArchivos() { }

        void mostrarInformacionDeEstacionPorCodigo(std::string codigo) { 
            Estacion* resultado=nullptr;
            if (estaciones.buscar(codigo, resultado)) {
                resultado->mostrarInformacion();
            } else {
                std::cout << "Estacion con codigo " << codigo << " no encontrada." << std::endl;
            }
         }

        void agregarEstacion(Estacion* estacion) { }

        bool eliminarEstacion(std::string codigo) { return false; }

        void listarEstacionesOrdenadas(int criterio) {
            int cantidad = estaciones.obtenerCantidad();

            if (cantidad == 0) {
                std::cout << "No hay estaciones para listar." << std::endl;
                return;
            }

            Estacion** arreglo = new Estacion*[cantidad];   //puntero de punteros porque cada elemento del arreglo es un puntero a Estacion. Sigue la misma logica que una lista
            estaciones.obtenerTodos(arreglo);

            bool porCapacidad = (criterio == 1);

            for (int i = 0; i < cantidad - 1; i++) {
                for (int j = 0; j < cantidad - 1 - i; j++) {
                    int izquierda = porCapacidad ? arreglo[j]->getCapacidadAnclajes()
                                                 : arreglo[j]->getBicisDisponibles();
                    int derecha = porCapacidad ? arreglo[j + 1]->getCapacidadAnclajes()
                                               : arreglo[j + 1]->getBicisDisponibles();

                    if (derecha < izquierda) {
                        Estacion* aux = arreglo[j];
                        arreglo[j] = arreglo[j + 1];
                        arreglo[j + 1] = aux;
                    }
                }
            }

            for (int i = 0; i < cantidad; i++) {
                arreglo[i]->mostrarInformacion();
            }

            delete[] arreglo;
        }

        void listarEstacionesConBajaOcupacion() { }

        void mostrarRecorridoMasCorto(std::string origen, std::string destino) { }

        void mostrarEstadisticasDelHash() { }

        int contarViajesDesdeEstacionEnRango(std::string codigo, int fechaDesde, int fechaHasta) { return 0; }

        void mostrarViajesYMinutosDeUsuario(int dni) { }

        Bicicleta* buscarBicicletaPorId(int id) { return nullptr; }

        void listarBicicletasOrdenadasPorId() { }

        int contarBicicletasAveriadas() { return 0; }

        void listarBicicletasConMasKm(int kmMinimo) { }

        void mostrarAlturaDelArbol() { }

        void retirarBicicleta(std::string codigoEstacion, int dni) { }

        void devolverBicicleta(std::string codigoEstacion) { }

        void enviarBicicletaAlTaller(int idBicicleta, int prioridad) { }

        void repararSiguienteBicicleta() { }

        void planificarRedistribucion(int capacidadCamion, std::string* codigos, int* faltantes, int cantidad) { }

        ~SistemaBicis() { }
};
