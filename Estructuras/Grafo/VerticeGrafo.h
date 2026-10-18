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

        ~VerticeGrafo() { }
};
