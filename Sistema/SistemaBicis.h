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
        SistemaBicis()
            : estaciones(101), viajes(nullptr, 0), ciclovias(nullptr, 0), bicicletas(nullptr, 0), taller(nullptr, 0, 0) {
        }

        void cargarDatosDesdeArchivos() { }

        Estacion* buscarEstacionPorCodigo(std::string codigo) { return nullptr; }

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

        void listarEstacionesOrdenadas(int criterio) { }

        void listarEstacionesConBajaOcupacion() { }

        void mostrarRecorridoMasCorto(std::string origen, std::string destino) { }

        void mostrarEstadisticasDelHash() {
            std::cout << "Estaciones en la tabla: " << estaciones.obtenerCantidad() << "\n";
            std::cout << "Colisiones: " << estaciones.obtenerColisiones() << "\n";
            std::cout << "Factor de carga: " << estaciones.calcularFactorDeCarga() << "\n";
        }

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

        ~SistemaBicis() {
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
