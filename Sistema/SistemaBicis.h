#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
        SistemaBicis()
            : estaciones(101), viajes(nullptr, 0), ciclovias(nullptr, 0), bicicletas(nullptr, 0), 
            taller(nullptr, 0, 0) {
        }

        void cargarDatosDesdeArchivos() {
            std::ifstream archivoEstaciones("Archivos/estaciones.txt");
            std::string linea;

            while (std::getline(archivoEstaciones, linea)) {
                std::istringstream flujo(linea);
                std::string codigo;
                std::string nombre;
                std::string barrio;
                int capacidadAnclajes;
                int bicisDisponibles;

                if (flujo >> codigo >> nombre >> barrio >> capacidadAnclajes
                        >> bicisDisponibles) {
                    agregarEstacion(new Estacion(codigo, nombre, barrio,
                                                    capacidadAnclajes, bicisDisponibles));
                }
            }

            std::ifstream archivoCiclovias("Archivos/ciclovias.txt");

            while (std::getline(archivoCiclovias, linea)) {
                std::istringstream flujo(linea);
                std::string origen;
                std::string destino;

                if (flujo >> origen >> destino) {
                    ciclovias.agregarArista(origen, destino);
                }
            }
        }

        void mostrarInformacionDeEstacionPorCodigo(std::string codigo) { 
            Estacion* resultado=nullptr;
            if (estaciones.buscar(codigo, resultado)) {
                resultado->mostrarInformacion();
            } else {
                std::cout << "Estacion con codigo " << codigo << " no encontrada." << std::endl;
            }
        }

        void agregarViaje(Viaje* viaje) {
            if (viaje == nullptr) {
                return;
            }
            viajes.insertarAlFinal(viaje);
        }

        void agregarEstacion(Estacion* estacion) { 
            if (estacion == nullptr) {
                return;
            }
            std::string codigo = estacion->getCodigo();

        
            if (codigo.length() != 3 || !estaciones.insertar(codigo, estacion)) {
                std::cout << "No se pudo agregar la estacion " << codigo
                            << ": el codigo es invalido o ya existe.\n";
                delete estacion;
                return;
            }

            ciclovias.agregarVertice(codigo);
            std::cout << "Estacion " << codigo << " agregada.\n";
        }

        bool eliminarEstacion(std::string codigo) {
            Estacion* estacion = nullptr;
            if (!estaciones.buscar(codigo, estacion)) {
                return false;
            }

            ciclovias.eliminarVertice(codigo);   
            estaciones.eliminar(codigo);         
            delete estacion;                     
            return true;
        }

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

                if (i < cantidad - 1) {
                    std::cout << "--------------------\n";
                }
            }

            delete[] arreglo;
        }

        void listarEstacionesConBajaOcupacion() {
            if (estaciones.obtenerCantidad() == 0) {
                std::cout << "No hay estaciones para listar." << std::endl;
                return;
            }

            Lista<Estacion*> listaEstaciones;
            estaciones.obtenerTodos(listaEstaciones);

            Lista<Estacion*> estacionesBajaOcupacion;
            NodoLista<Estacion*>* actual = listaEstaciones.obtenerPrimero();

            while (actual != nullptr) {
                Estacion* estacion = actual->getDato();

                if (estacion->calcularPorcentajeOcupacion() < 20.0) {
                    estacionesBajaOcupacion.insertarAlFinal(estacion);
                }

                actual = actual->getSiguiente();
            }

            NodoLista<Estacion*>* baja = estacionesBajaOcupacion.obtenerPrimero();

            if (baja == nullptr) {
                std::cout << "No hay estaciones con baja ocupacion." << std::endl;
                return;
            }

            while (baja != nullptr) {
                baja->getDato()->mostrarInformacion();
                baja = baja->getSiguiente();
            }
        }

        void mostrarRecorridoMasCorto(std::string origen, std::string destino) {
            Lista<std::string> camino;
            int largo = 0;

            if (!ciclovias.caminoMasCorto(origen, destino, camino, largo)) {
                std::cout << "No existe un recorrido entre " << origen
                            << " y " << destino << "." << std::endl;
                return;
            }

            std::cout << "Recorrido mas corto (" << largo << " tramos): ";

            NodoLista<std::string>* actual = camino.obtenerPrimero();

            while (actual != nullptr) {
                std::cout << actual->getDato();

                actual = actual->getSiguiente();

                if (actual != nullptr) {
                    std::cout << " -> ";
                }
            }

            std::cout << std::endl;
        }

        void mostrarEstadisticasDelHash() {
            std::cout << "Estaciones en la tabla: " << estaciones.obtenerCantidad() << "\n";
            std::cout << "Colisiones: " << estaciones.obtenerColisiones() << "\n";
            std::cout << "Factor de carga: " << estaciones.calcularFactorDeCarga() << "\n";
        }

        int contarViajesDesdeEstacionEnRango(std::string codigo, int fechaDesde, int fechaHasta) {
            if (fechaDesde > fechaHasta) {
                return 0;
            }

            NodoLista<Viaje*>* actual = viajes.obtenerPrimero();
            int cantidad = 0;

            while (actual != nullptr) {
                Viaje* viaje = actual->getDato();

            if (viaje != nullptr &&
                viaje->getEstacionOrigen() == codigo &&
                viaje->getFecha() >= fechaDesde &&
                viaje->getFecha() <= fechaHasta) {
                    
                    cantidad++;
                }

            actual = actual->getSiguiente();
            }

            return cantidad;
        }

        void mostrarViajesYMinutosDeUsuario(int dni) {
            NodoLista<Viaje*>* actual = viajes.obtenerPrimero();
            int totalMinutos = 0;
            bool encontrado = false;

            while (actual != nullptr) {
                Viaje* viaje = actual->getDato();

                if (viaje != nullptr && viaje->getDniUsuario() == dni) {
                    viaje->mostrarInformacion();
                    std::cout << "--------------------\n";

                    totalMinutos += viaje->getDuracionMin();
                    encontrado = true;
                }

                actual = actual->getSiguiente();
            }

            if (!encontrado) {
                std::cout << "No se encontraron viajes para el DNI "
                    << dni << ".\n";
                return;
            }

            std::cout << "Total de minutos pedaleados: "
                    << totalMinutos << '\n';
        }

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

        ~SistemaBicis() {
            NodoLista<Viaje*>* actualViaje = viajes.obtenerPrimero();
            while (actualViaje != nullptr) {
                delete actualViaje->getDato();
                actualViaje = actualViaje->getSiguiente();
            }

            int cantidad = estaciones.obtenerCantidad();
            if (cantidad > 0) {
                Estacion** todas = new Estacion*[cantidad];
                estaciones.obtenerTodos(todas);
                for (int i = 0; i < cantidad; i++) {
                    delete todas[i];
                }
                delete[] todas;
            }
        }
};
