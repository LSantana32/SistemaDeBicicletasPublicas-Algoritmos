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
            taller() {
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

            
            std::ifstream archivoBicicletas("Archivos/bicicletas.txt");

            while (std::getline(archivoBicicletas, linea)) {
                std::istringstream flujo(linea);
                
                int id;
                std::string codigoEstacion;
                std::string tipo;
                std::string estado;
                int kilometros;

                if (flujo >> id >> codigoEstacion >> tipo >> estado >> kilometros) {
                    agregarBicicleta(id, codigoEstacion, tipo, estado, kilometros);
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

        void agregarBicicleta(int id, std::string codigoEstacion, std::string tipo, std::string estado, int kilometros) {
            Estacion* estacion = nullptr;
            if (!estaciones.buscar(codigoEstacion, estacion)) {
                std::cout << "No se pudo agregar la bicicleta " << id
                        << ": la estacion " << codigoEstacion
                        << " no existe.\n";
                return;
            }

            Bicicleta* bicicleta = new Bicicleta(
                id, codigoEstacion, tipo, estado, kilometros);

            if (!bicicletas.insertar(id, bicicleta)) {
                std::cout << "No se pudo agregar la bicicleta " << id
                        << ": el ID ya existe.\n";
                delete bicicleta;
                return;
            }

            std::cout << "Bicicleta " << id << " agregada.\n";
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
            int cantidadEstaciones = estaciones.obtenerCantidad();

            if (cantidadEstaciones == 0) {
                std::cout << "No hay estaciones para listar." << std::endl;
                return;
            }

            Estacion** arregloEstaciones = new Estacion*[cantidadEstaciones];   //puntero de punteros porque cada elemento del arreglo es un puntero a Estacion. Sigue la misma logica que una lista
            estaciones.obtenerTodos(arregloEstaciones);

            bool porCapacidad = (criterio == 1);

            for (int i = 0; i < cantidadEstaciones - 1; i++) {
                for (int j = 0; j < cantidadEstaciones - 1 - i; j++) {
                    int nodoIzquierdo = porCapacidad ? arregloEstaciones[j]->getCapacidadAnclajes()
                                                : arregloEstaciones[j]->getBicisDisponibles();
                    int nodoDerecho = porCapacidad ? arregloEstaciones[j + 1]->getCapacidadAnclajes()
                                                : arregloEstaciones[j + 1]->getBicisDisponibles();

                    if (nodoDerecho < nodoIzquierdo) {
                        Estacion* aux = arregloEstaciones[j];
                        arregloEstaciones[j] = arregloEstaciones[j + 1];
                        arregloEstaciones[j + 1] = aux;
                    }
                }
            }

            for (int i = 0; i < cantidadEstaciones; i++) {
                arregloEstaciones[i]->mostrarInformacion();

                if (i < cantidadEstaciones - 1) {
                    std::cout << "--------------------\n";
                }
            }

            delete[] arregloEstaciones;
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

        Bicicleta* buscarBicicletaPorId(int id) { 
            Bicicleta* resultado = nullptr;

            if(bicicletas.buscar(id, resultado)) {
                return resultado;
            }
            return nullptr;
        }

        void listarBicicletasOrdenadasPorId() {
            int cantidad = bicicletas.obtenerCantidad();

            if(cantidad == 0){
                std::cout << "No hay bicicletas para listar.\n";
                return;
            }

            Bicicleta** arreglo = new Bicicleta*[cantidad];

            bicicletas.obtenerEnInorder(arreglo);

            for (int i = 0; i < cantidad; i++) {
                if (arreglo[i] != nullptr) {
                    arreglo[i]->mostrarInformacion();

                    if (i < cantidad - 1) {
                        std::cout << "--------------------\n";
                    }
                }
            }
            delete[] arreglo;
        }

        int contarBicicletasAveriadas() {
            int cantidad = bicicletas.obtenerCantidad();
            if (cantidad == 0) {
                return 0;
            }

            Bicicleta** arreglo = new Bicicleta*[cantidad];
            bicicletas.obtenerEnInorder(arreglo);  

            int averiadas = 0;
            for (int i = 0; i < cantidad; i++) {
                if (arreglo[i]->estaAveriada()) {
                    averiadas++;
                }
            }

            delete[] arreglo;   
            return averiadas;

        }

        void listarBicicletasConMasKm(int kmMinimo) {
            int cantidadBicicletas = bicicletas.obtenerCantidad(); //1

            if (cantidadBicicletas == 0) { //1
                std::cout << "No hay bicicletas para listar.\n"; 
                return;
            }

            Bicicleta** arregloBicis = new Bicicleta*[cantidadBicicletas];  //2
            bicicletas.obtenerEnInorder(arregloBicis); //n

            bool encontrado = false; //1

            for (int i = 0; i < cantidadBicicletas; i++) { // 1 + n+n *(...
                if (arregloBicis[i] != nullptr //+1
                    && arregloBicis[i]->getKilometros() > kmMinimo) {
                    if (encontrado) { //+1
                        std::cout << "--------------------\n";
                    }

                    arregloBicis[i]->mostrarInformacion(); //+1
                    encontrado = true; //+1)
                }
            }

            delete[] arregloBicis; //1

            if (!encontrado) { //1
                std::cout << "No hay bicicletas con mas de " << kmMinimo
                        << " kilometros.\n";
            }                                                     //1+1+2+n+1+1+n+n*(1+1+1+1)+1+1= 6 + 2n + 4n + 2 = 8 +6n
        }                                                        // O(n) 

        void mostrarAlturaDelArbol() {
            int altura = bicicletas.calcularAltura();
            std::cout << "Altura del arbol de bicicletas: " << altura << std::endl;
        }

        void retirarBicicleta(std::string codigoEstacion, int dni, int fechaActual) {
            Estacion* estacion = nullptr;
            //Verificar que la estacion existe.
            if (!estaciones.buscar(codigoEstacion, estacion)) {
                std::cout << "Estacion con codigo " << codigoEstacion << " no encontrada." << std::endl;
                return;
            }

            //Verificar que el usuario no tiene un viaje en curso. Un viaje esta en curso cuando no tiene estacion destino.
            Viaje* ultimoViaje = viajes.obtenerUltimoViajeDe(dni);
            if (ultimoViaje != nullptr && ultimoViaje->getEstacionDestino() == "") {
                std::cout << "El usuario con DNI " << dni << " ya tiene un viaje en curso." << std::endl;
                return;
            }   

            if (!estacion->hayBicicletasDisponibles()) {
                estacion->retirarBicicleta(dni);
                std::cout << "No hay bicicletas disponibles en la estacion " << codigoEstacion
                            << ". Se ha agregado a la cola de espera del usuario con DNI " << dni << "." << std::endl;
                return;
            }

            Bicicleta* bicicleta =
                bicicletas.obtenerBicicletaDisponibleEnEstacion(codigoEstacion);
            if (bicicleta == nullptr) {
                std::cout << "No hay una bicicleta disponible registrada en la estacion "
                            << codigoEstacion << ".\n";
                return;
            }

            if (estacion->retirarBicicleta(dni)) {
                bicicleta->iniciarViaje();

                // El viaje queda abierto hasta que el usuario devuelve la bicicleta.
                Viaje* ultimoViaje =
                    viajes.obtenerEnPosicion(viajes.obtenerLargo() - 1);
                int nuevoId = ultimoViaje != nullptr ? ultimoViaje->getId() + 1 : 1;
                Viaje* viaje = new Viaje(
                    nuevoId, bicicleta->getId(), dni, codigoEstacion, "",
                    fechaActual, 0);
                viajes.insertarAlFinal(viaje);

                std::cout << "Bicicleta retirada exitosamente de la estacion "
                            << codigoEstacion << "." << std::endl;
            }
        }

        void devolverBicicleta( std::string codigoEstacion, int dni, int duracionMin) {
            Estacion* estacion = nullptr;
            if (!estaciones.buscar(codigoEstacion, estacion)) {
                std::cout << "Estacion con codigo " << codigoEstacion << " no encontrada." << std::endl;
                return;
            }

            Viaje* viaje = viajes.obtenerUltimoViajeDe(dni);
            if (viaje == nullptr || viaje->getEstacionDestino() != "") {
                std::cout << "El usuario con DNI " << dni
                            << " no tiene un viaje en curso.\n";
                return;
            }

            Bicicleta* bicicleta = nullptr;
            if (!bicicletas.buscar(viaje->getIdBici(), bicicleta)
                || bicicleta == nullptr) {
                std::cout << "No se encontro la bicicleta del viaje del usuario "
                            << dni << ".\n";
                return;
            }

            int resultado = estacion->devolverBicicleta();
            if (resultado == -2) {
                std::cout << "No se puede devolver la bicicleta a la estacion " << codigoEstacion
                                << ". La estacion esta llena." << std::endl;
                return;
            }

            bicicleta->setCodigoEstacion(codigoEstacion);
            viaje->setEstacionDestino(codigoEstacion);
            viaje->setDuracionMin(duracionMin);

            if (resultado == -1) {
                std::cout << "Bicicleta devuelta exitosamente a la estacion " << codigoEstacion
                            << ". No hay usuarios en espera." << std::endl;
            } else {
                std::cout << "Bicicleta devuelta exitosamente a la estacion " << codigoEstacion
                            << ". Se ha asignado al usuario con DNI " << resultado
                            << " que estaba en espera." << std::endl;

                Viaje* ultimoViaje =
                    viajes.obtenerEnPosicion(viajes.obtenerLargo() - 1);
                int nuevoId =
                    ultimoViaje != nullptr ? ultimoViaje->getId() + 1 : 1;
                Viaje* nuevoViaje = new Viaje(
                    nuevoId, viaje->getIdBici(), resultado, codigoEstacion, "",
                    viaje->getFecha(), 0);
                viajes.insertarAlFinal(nuevoViaje);
                bicicleta->iniciarViaje();
            }
        }

        void enviarBicicletaAlTaller(int idBicicleta, int prioridad) { 
            Bicicleta* bicicleta = buscarBicicletaPorId(idBicicleta);
            if (bicicleta == nullptr) {
                std::cout << "No existe una bicicleta con ID " << idBicicleta << "." << std::endl;
                return;
            }
            if (!bicicleta->estaAveriada()) {
                std::cout << "La bicicleta " << idBicicleta
                          << " no esta averiada: no se envia al taller." << std::endl;
                return;
            }
            if (prioridad < 1 || prioridad > 3) {
                std::cout << "La prioridad tiene que ser 1, 2 o 3." << std::endl;
                return;
            }
            if (bicicleta->esElectrica()) {
                prioridad = 1;   
            }

            taller.insertar(bicicleta, prioridad);
            std::cout << "Bicicleta " << idBicicleta << " enviada al taller con prioridad "
                      << prioridad << "." << std::endl;
        }

        void repararSiguienteBicicleta() { 
            if (taller.estaVacio()) {
                std::cout << "No hay bicicletas en el taller." << std::endl;
                return;
            }

            Bicicleta* bicicleta = taller.extraerMinimo();
            bicicleta->setEstado("OK");
            std::cout << "Se reparo la bicicleta " << bicicleta->getId() << ":" << std::endl;
            bicicleta->mostrarInformacion();
        }

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
