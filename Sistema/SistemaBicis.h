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

        /*
            Complejidad Algoritmica
            n = cantidad de viajes en el sistema
            T(n) = 1 + 1 + 2 + 2 + n + 1 + n * (7 + 2) + 2 + 2 + 1 = 12 + n + 9n = 12 + 10n = O(n)
        */

        int contarViajesDesdeEstacionEnRango(std::string codigo, int fechaDesde, int fechaHasta) {
            if (fechaDesde > fechaHasta) { // 1
                return 0; // 1
            }

            NodoLista<Viaje*>* actual = viajes.obtenerPrimero(); // 2
            int cantidad = 0; // 2

            while (actual != nullptr) { // n + 1
                Viaje* viaje = actual->getDato(); // 2

                if (viaje != nullptr &&
                viaje->getEstacionOrigen() == codigo &&
                viaje->getFecha() >= fechaDesde &&
                viaje->getFecha() <= fechaHasta) { // 7
                    cantidad++; // 2
                }

            actual = actual->getSiguiente(); // 2
            }

            return cantidad; // 1
        }

        /*
            Complejidad Algoritmica
            n = cantidad de viajes en el sistema
            T(n) = 2 + 2 + 2 + n + 1 + n * (2 + 4 + 1 + 1 + 2 + 2 + 2) + 1 + 1 + 1 + 1 = 11 + n + 14n = 11 + 15n = O(n)
        */
        void mostrarViajesYMinutosDeUsuario(int dni) {
            NodoLista<Viaje*>* actual = viajes.obtenerPrimero(); // 2
            int totalMinutos = 0; // 2
            bool encontrado = false; // 2

            while (actual != nullptr) { // n + 1
                Viaje* viaje = actual->getDato(); // 2

                if (viaje != nullptr && viaje->getDniUsuario() == dni) { // 4
                    viaje->mostrarInformacion(); // 1
                    std::cout << "--------------------\n"; // 1

                    totalMinutos += viaje->getDuracionMin(); // 2
                    encontrado = true; // 2
                }

                actual = actual->getSiguiente(); // 2
            }

            if (!encontrado) { // 1
                std::cout << "No se encontraron viajes para el DNI " 
                    << dni << ".\n"; // 1
                return; // 1
            }

            std::cout << "Total de minutos pedaleados: "
                    << totalMinutos << '\n'; // 1
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

        /*
            Complejidad Algoritmica
            n = cantidad de bicicletas en el sistema
            T(n) = 2 + 1 + 1 + 1 + 2 + 1 + 2 + 2 + n + 1 + 2 + n * (4 + 1 + 1 + 1 + 1) + 1 + 1 + 1 = 18 + n + 8n = 18 + 9n = O(n)
        */
        void listarBicicletasConMasKm(int kmMinimo) {
            int cantidadBicicletas = bicicletas.obtenerCantidad(); // 2

            if (cantidadBicicletas == 0) { //1
                std::cout << "No hay bicicletas para listar.\n"; // 1
                return; // 1
            }

            Bicicleta** arregloBicis = new Bicicleta*[cantidadBicicletas];  // 2
            bicicletas.obtenerEnInorder(arregloBicis); // 1

            bool encontrado = false; // 2

            for (int i = 0; i < cantidadBicicletas; i++) { // 2 + n + 1 + 2
                if (arregloBicis[i] != nullptr 
                    && arregloBicis[i]->getKilometros() > kmMinimo) { // 4
                    if (encontrado) { // 1
                        std::cout << "--------------------\n"; // 1
                    }

                    arregloBicis[i]->mostrarInformacion(); // 1
                    encontrado = true; // 1
                }
            }

            delete[] arregloBicis; // 1

            if (!encontrado) { // 1
                std::cout << "No hay bicicletas con mas de " << kmMinimo
                        << " kilometros.\n"; // 1
            }
        }

        void mostrarAlturaDelArbol() {
            int altura = bicicletas.calcularAltura();
            std::cout << "Altura del arbol de bicicletas: " << altura << std::endl;
        }

        /*
            Complejidad Algoritmica
            n = cantidad de viajes en el sistema
            b = cantidad de bicicletas en el sistema
            T(n) = 2 + 1 + 1 + 1 + n + 4 + 1 + 1 + 1 + 1 + 1 + 1 + b + 1 + 1 + 1 + 1 + 1 + n + 2 + 2 + 1 + 1 + 1 = 
                    22 + b + 2n = O(b + n)
        */

        void retirarBicicleta(std::string codigoEstacion, int dni, int fechaActual) {
            Estacion* estacion = nullptr; // 2
            //Verificar que la estacion existe.
            if (!estaciones.buscar(codigoEstacion, estacion)) { // 1
                std::cout << "Estacion con codigo " << codigoEstacion << " no encontrada." << std::endl; // 1
                return; // 1
            }

            //Verificar que el usuario no tiene un viaje en curso. Un viaje esta en curso cuando no tiene estacion destino.
            Viaje* ultimoViaje = viajes.obtenerUltimoViajeDe(dni); // n
            if (ultimoViaje != nullptr && ultimoViaje->getEstacionDestino() == "") { // 4
                std::cout << "El usuario con DNI " << dni << " ya tiene un viaje en curso." << std::endl; // 1
                return; // 1
            }   

            if (!estacion->hayBicicletasDisponibles()) { // 1
                estacion->retirarBicicleta(dni); // 1
                std::cout << "No hay bicicletas disponibles en la estacion " << codigoEstacion 
                            << ". Se ha agregado a la cola de espera del usuario con DNI " << dni << "." << std::endl; // 1
                return; // 1
            }

            Bicicleta* bicicleta =
                bicicletas.obtenerBicicletaDisponibleEnEstacion(codigoEstacion); // b
            if (bicicleta == nullptr) { // 1
                std::cout << "No hay una bicicleta disponible registrada en la estacion "
                            << codigoEstacion << ".\n"; // 1
                return; // 1
            }

            if (estacion->retirarBicicleta(dni)) { // 1
                bicicleta->iniciarViaje(); // 1

                // El viaje queda abierto hasta que el usuario devuelve la bicicleta.
                Viaje* ultimoViaje =
                    viajes.obtenerEnPosicion(viajes.obtenerLargo() - 1); // n
                int nuevoId = ultimoViaje != nullptr ? ultimoViaje->getId() + 1 : 1; // 2
                Viaje* viaje = new Viaje(
                    nuevoId, bicicleta->getId(), dni, codigoEstacion, "",
                    fechaActual, 0); // 2
                viajes.insertarAlFinal(viaje); // 1

                std::cout << "Bicicleta retirada exitosamente de la estacion "
                            << codigoEstacion << "." << std::endl; // 1
            }
        }

        /*
            Compejidad Algoritmica
            n = cantidad de viajes en el sistema
            b = cantidad de bicicletas en el sistema
            T(n) = 2 + 1 + 1 + 1 + n + 2 + 1 + 1 + b + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + n + 1 + 1 + n + 1 = 
                    22 + b + 3n = O(b + n)
        */
        void devolverBicicleta( std::string codigoEstacion, int dni, int duracionMin) {
            Estacion* estacion = nullptr; // 2
            if (!estaciones.buscar(codigoEstacion, estacion)) { // 1
                std::cout << "Estacion con codigo " << codigoEstacion << " no encontrada." << std::endl; // 1
                return; // 1
            }

            Viaje* viaje = viajes.obtenerUltimoViajeDe(dni); // n
            if (viaje == nullptr || viaje->getEstacionDestino() != "") { // 2
                std::cout << "El usuario con DNI " << dni
                            << " no tiene un viaje en curso.\n"; // 1
                return; // 1
            }

            Bicicleta* bicicleta = nullptr;
            if (!bicicletas.buscar(viaje->getIdBici(), bicicleta) 
                || bicicleta == nullptr) { // b + 1
                std::cout << "No se encontro la bicicleta del viaje del usuario " 
                            << dni << ".\n"; // 1
                return; // 1
            }

            int resultado = estacion->devolverBicicleta(); // 1
            if (resultado == -2) { // 1
                std::cout << "No se puede devolver la bicicleta a la estacion " << codigoEstacion
                                << ". La estacion esta llena." << std::endl; // 1
                return; // 1
            }

            bicicleta->setCodigoEstacion(codigoEstacion); // 1
            viaje->setEstacionDestino(codigoEstacion); // 1
            viaje->setDuracionMin(duracionMin); // 1

            if (resultado == -1) { // 1
                std::cout << "Bicicleta devuelta exitosamente a la estacion " << codigoEstacion 
                            << ". No hay usuarios en espera." << std::endl; // 1
            } else { 
                std::cout << "Bicicleta devuelta exitosamente a la estacion " << codigoEstacion
                            << ". Se ha asignado al usuario con DNI " << resultado
                            << " que estaba en espera." << std::endl; // 1

                Viaje* ultimoViaje =
                    viajes.obtenerEnPosicion(viajes.obtenerLargo() - 1); // n
                int nuevoId =
                    ultimoViaje != nullptr ? ultimoViaje->getId() + 1 : 1; // 1
                Viaje* nuevoViaje = new Viaje(
                    nuevoId, viaje->getIdBici(), resultado, codigoEstacion, "",
                    viaje->getFecha(), 0); // 1
                viajes.insertarAlFinal(nuevoViaje); // n
                bicicleta->iniciarViaje(); // 1
            }
        }

        /*
            Compejidad Algoritmica
            n = cantidad de viajes en el sistema
            b = cantidad de bicicletas en el sistema
            T(n) = b + 1 + 1 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 + 2 + n + 1 = 14 + b + n = O(b + n)
        */
        void enviarBicicletaAlTaller(int idBicicleta, int prioridad) { 
            Bicicleta* bicicleta = buscarBicicletaPorId(idBicicleta); // b
            if (bicicleta == nullptr) { // 1
                std::cout << "No existe una bicicleta con ID " << idBicicleta << "." << std::endl; // 1
                return; // 1
            }
            if (!bicicleta->estaAveriada()) { // 2
                std::cout << "La bicicleta " << idBicicleta 
                            << " no esta averiada: no se envia al taller." << std::endl; // 1
                return; // 1
            }
            if (prioridad < 1 || prioridad > 3) { // 1
                std::cout << "La prioridad tiene que ser 1, 2 o 3." << std::endl; // 1
                return; // 1
            }
            if (bicicleta->esElectrica()) { // 1
                prioridad = 1; // 2
            }

            taller.insertar(bicicleta, prioridad); // n
            std::cout << "Bicicleta " << idBicicleta << " enviada al taller con prioridad "
                        << prioridad << "." << std::endl; // 1
        }

        /*
            Compejidad Algoritmica
            n = cantidad de bicicletas en el taller
            T(n) = 2 + 1 + 1 + n + 1 + 1 + 1 = 7 + n = O(n)
        */
        void repararSiguienteBicicleta() { 
            if (taller.estaVacio()) { // 2
                std::cout << "No hay bicicletas en el taller." << std::endl; // 1
                return; // 1
            }

            Bicicleta* bicicleta = taller.extraerMinimo(); // n
            bicicleta->setEstado("OK"); // 1
            std::cout << "Se reparo la bicicleta " << bicicleta->getId() << ":" << std::endl; // 1
            bicicleta->mostrarInformacion(); // 1
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
