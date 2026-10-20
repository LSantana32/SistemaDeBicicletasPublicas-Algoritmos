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

        T getDato() { return dato; }

        VerticeGrafo<T>* getSiguiente() { return siguiente; }

        void setSiguiente(VerticeGrafo<T>* nodo) { siguiente = nodo; }

        void agregarAristaHacia(VerticeGrafo<T>* destino) {
            if (destino == nullptr || destino == this) {
                return;
            }

            AristaGrafo<T>* actual = primeraArista;
            while (actual != nullptr) {
                if (actual->getDestino() == destino) {
                    return;
                }
                actual = actual->getSiguiente();
            }

            AristaGrafo<T>* nuevaArista =
                new AristaGrafo<T>(destino, primeraArista);
            primeraArista = nuevaArista;
        }

        void eliminarAristaHacia(VerticeGrafo<T>* destino) {
            AristaGrafo<T>* actual = primeraArista;
            AristaGrafo<T>* anterior = nullptr;

            while (actual != nullptr) {
                AristaGrafo<T>* siguienteArista = actual->getSiguiente();

                if (actual->getDestino() == destino) {
                    if (anterior == nullptr) {
                        primeraArista = siguienteArista;
                    } else {
                        anterior->setSiguiente(siguienteArista);
                    }
                    delete actual;
                } else {
                    anterior = actual;
                }

                actual = siguienteArista;
            }
        }

        void setVisitado(bool visitado) { 
            this->visitado = visitado; 
        }

        bool getVisitado() { 
            return visitado; 
        }

        AristaGrafo<T>* getPrimeraArista() { 
            return primeraArista; 
        }

        ~VerticeGrafo() {
            AristaGrafo<T>* actual = primeraArista;

            while (actual != nullptr) {
                AristaGrafo<T>* siguienteArista = actual->getSiguiente();
                delete actual;
                actual = siguienteArista;
            }
        }
};
