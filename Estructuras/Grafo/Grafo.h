#pragma once

#include "VerticeGrafo.h"
#include "../Cola/Cola.h"
#include "../Lista/Lista.h"

template <class T>
struct NodoBFS {
    VerticeGrafo<T>* vertice;
    VerticeGrafo<T>* padre;
    NodoBFS(VerticeGrafo<T>* v, VerticeGrafo<T>* p) : vertice(v), padre(p) {}
    NodoBFS() : vertice(nullptr), padre(nullptr) {}
    
    VerticeGrafo<T>* getVertice() { return vertice; }

    VerticeGrafo<T>* getPadre() { return padre; }
};

template <class T>
class Grafo {
    private:
        VerticeGrafo<T>* primerVertice;
        int cantidadVertices;

        VerticeGrafo<T>* buscarVertice(T dato) {
            VerticeGrafo<T>* actual = primerVertice;
            while (actual != nullptr) {
                if (actual->getDato() == dato) {
                    return actual;
                }
                actual = actual->getSiguiente();
            }
            return nullptr;
        }

        void reiniciarMarcas() { }

        // Metodo usado para obtener el padre de un vertice en el recorrido BFS.
        VerticeGrafo<T>* obtenerPadre(Lista<NodoBFS<T>>& nodosBFS, VerticeGrafo<T>* vertice) {
            for (int i = 0; i < nodosBFS.obtenerLargo(); i++) {
                NodoBFS<T> nodo = nodosBFS.obtenerEnPosicion(i);
                if (nodo.getVertice() == vertice) {
                    return nodo.getPadre();
                }
            }
            return nullptr;
        }

    public:
        Grafo(VerticeGrafo<T>* primerVertice, int cantidadVertices) {
            this->primerVertice = primerVertice;
            this->cantidadVertices = cantidadVertices;
        }

        void agregarVertice(T dato) {
            if (existeVertice(dato)) { // Si el vértice ya existe, no se agrega 
                return;
            }

            //El nuevo vertice pasa a ser el primero, y su siguiente es el anterior primer vertice
            VerticeGrafo<T>* nuevoVertice =
                new VerticeGrafo<T>(dato, nullptr, primerVertice, false, nullptr); 

            primerVertice = nuevoVertice;
            cantidadVertices++;
        }

        bool eliminarVertice(T dato) {
            VerticeGrafo<T>* actual = primerVertice;
            VerticeGrafo<T>* anterior = nullptr;

            //Recorro los vertices hasta encontrar el que busco
            while (actual != nullptr && !(actual->getDato() == dato)) {
                anterior = actual;
                actual = actual->getSiguiente();
            }

            if (actual == nullptr) { // Si no existe no se elimina nada
                return false;
            }

            if (anterior == nullptr) { // Si el vertice a eliminar es el primero, actualizo el primer vertice.
                primerVertice = actual->getSiguiente();
            } else {
                anterior->setSiguiente(actual->getSiguiente()); // Si no lo es, actualizo el siguiente del anterior al eliminar.
            }

            // Elimino todas las aristas que apuntan al vertice eliminado.
            VerticeGrafo<T>* otro = primerVertice; 
            while (otro != nullptr) {
                otro->eliminarAristaHacia(actual);
                otro = otro->getSiguiente();
            }

            delete actual;
            cantidadVertices--;
            return true;
        }

        void agregarArista(T origen, T destino) {
            VerticeGrafo<T>* verticeOrigen = buscarVertice(origen);
            VerticeGrafo<T>* verticeDestino = buscarVertice(destino);

            if (verticeOrigen == nullptr || verticeDestino == nullptr || verticeOrigen == verticeDestino) { 
                return;
            }

            verticeOrigen->agregarAristaHacia(verticeDestino);
            verticeDestino->agregarAristaHacia(verticeOrigen);
        }

        bool existeVertice(T dato) { return buscarVertice(dato) != nullptr; }

        void reiniciarVisitas() { 
            VerticeGrafo<T>* verticeActual = primerVertice;
            while(verticeActual != nullptr) {
                verticeActual->setVisitado(false);
                verticeActual = verticeActual->getSiguiente();
            }
        }

        //Camino más corto entre dos estaciones usando BFS
        bool caminoMasCorto(T origen, T destino, Lista<T> &camino, int& largo) { 
            camino.vaciar();
            reiniciarVisitas();
            largo = -1;

            //verifico que existan los vertices
            VerticeGrafo<T>* verticeOrigen = buscarVertice(origen);
            VerticeGrafo<T>* verticeDestino = buscarVertice(destino);
            if (verticeOrigen == nullptr || verticeDestino == nullptr) {
                return false;
            }

            Cola<VerticeGrafo<T>*> cola;
            Lista<NodoBFS<T>> caminoNodosBFS;

            // inicio el BFS desde el vertice origen
            cola.encolar(verticeOrigen);
            verticeOrigen->setVisitado(true);
            caminoNodosBFS.insertarAlFinal(NodoBFS<T>(verticeOrigen, nullptr));

            bool encontrado = (verticeOrigen == verticeDestino);

            // Si la cola esta vacia o ya encontre el detino, para el while
            while (!cola.estaVacia() && !encontrado) {
                VerticeGrafo<T>* verticeActual = cola.desencolar();
                AristaGrafo<T>* aristaActual = verticeActual->getPrimeraArista();

                // Recorro todas las aristas del vertice actual
                while (aristaActual != nullptr) {
                    VerticeGrafo<T>* vecino = aristaActual->getDestino();

                    if (!vecino->getVisitado()) {
                        vecino->setVisitado(true);
                        cola.encolar(vecino);
                        caminoNodosBFS.insertarAlFinal(NodoBFS<T>(vecino, verticeActual));

                        //Si ya encontre el vertice destino corto el while de aristas.
                        if (vecino == verticeDestino) {
                            encontrado = true;
                            break;
                        }
                    }

                    aristaActual = aristaActual->getSiguiente();
                }
            }

            if (!encontrado) {
                return false;
            }

            // reconstruyo desde el destino hasta el origen insertando al frente,
            // así el camino queda en orden origen -> destino.
            int cantidadEstaciones = 0;
            VerticeGrafo<T>* actual = verticeDestino;

            // Reconstruyo el camino desde el destino hacia el origen usando los padres almacenados en caminoNodosBFS
            while (actual != nullptr) {
                camino.insertarEnPosicion(actual->getDato(), 0);
                cantidadEstaciones++;
                actual = obtenerPadre(caminoNodosBFS, actual);
            }

            largo = cantidadEstaciones - 1; // cantidad de aristas del camino
            return true; 
        }

        ~Grafo() {
            VerticeGrafo<T>* actual = primerVertice;

            while (actual != nullptr) {
                VerticeGrafo<T>* siguienteVertice = actual->getSiguiente();
                delete actual;
                actual = siguienteVertice;
            }
        }
};
