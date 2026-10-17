#pragma once

#include "AristaGrafo.h"

template <class T>
class VerticeGrafo {
    private:
        T dato;
        AristaGrafo<T>* primeraArista;
        VerticeGrafo<T>* siguiente;
        bool visitado;
        VerticeGrafo<T>* anterior;

    public:
        VerticeGrafo(T dato, AristaGrafo<T>* primeraArista, VerticeGrafo<T>* siguiente, bool visitado, VerticeGrafo<T>* anterior) {
            this->dato = dato;
            this->primeraArista = primeraArista;
            this->siguiente = siguiente;
            this->visitado = visitado;
            this->anterior = anterior;
        }

        T getDato() { return T(); }

        void agregarAristaHacia(VerticeGrafo<T>* destino) { }

        void eliminarAristaHacia(VerticeGrafo<T>* destino) { }

        void setVisitado(bool visitado) { 
            this->visitado = visitado; 
        }

        bool getVisitado() { 
            return visitado; 
        }

        AristaGrafo<T>* getPrimeraArista() { 
            return primeraArista; 
        }

        bool tieneCaminoHacia(VerticeGrafo<T>* destino) { 
            AristaGrafo<T>* aristaActual = primeraArista;
            while (aristaActual != nullptr) {
                if (aristaActual->getDestino() == destino) {
                    return true;
                }
                aristaActual = aristaActual->getSiguiente();
            }
            return false;
        }

        int cantEstacionesHasta(VerticeGrafo<T>* destino) { 
            if (this == destino) {
                return 0;
            }

            if (!tieneCaminoHacia(destino)) {
                return -1; // No hay camino hacia el destino
            }
            
            int count = 1; // Contamos la arista hacia el destino
            AristaGrafo<T>* aristaActual = primeraArista;
            while (aristaActual != nullptr) {
                if (aristaActual->getDestino() == destino) {
                    return count;
                }
                aristaActual = aristaActual->getSiguiente();
                count++;
            }
        }

        ~VerticeGrafo() { }
};
