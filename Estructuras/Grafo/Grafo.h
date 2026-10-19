#pragma once

#include "VerticeGrafo.h"
#include "../Cola/Cola.h"

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

        VerticeGrafo<T>* buscarVertice(T dato) { return nullptr; }

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

        void agregarVertice(T dato) { }

        bool eliminarVertice(T dato) { return false; }

        void agregarArista(T origen, T destino) { }

        bool existeVertice(T dato) { return false; }

        void reiniciarVisitas() { 
            VerticeGrafo<T>* verticeActual = primerVertice;
            while(verticeActual != nullptr) {
                verticeActual->setVisitado(false);
                verticeActual = verticeActual->getSiguiente();
            }
        }

        //Listar las estaciones con poca ocupación (menos del 20% de ocupación)
        Lista<T> estacionesConPocaOcupacion() { 
            Lista<T> listaResultados;
            VerticeGrafo<T>* verticeActual = primerVertice;
            // cada vertice tiene el dato de la estacion, su siguiente y anterior vertice.
            // por eso uso un while para recorrer toda la lista de vertices.
            // solo recorro los vertices, no las aristas, solo tengo que revisar las estaciones, no sus conexiones.
            while(verticeActual != nullptr) {
                double porcentajeOcupacion = verticeActual->getDato().calcularPorcentajeOcupacion();
                if (porcentajeOcupacion < 20.0) {
                    listaResultados.insertarAlFinal(verticeActual->getDato());
                }
                verticeActual = verticeActual->getSiguiente();
            }
            return listaResultados; 
        }

        //Camino más corto entre dos estaciones usando BFS
        bool caminoMasCorto(T origen, T destino, Lista<T> &camino, int& largo) { 
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

        ~Grafo() { }
};
