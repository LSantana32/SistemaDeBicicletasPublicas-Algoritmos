#pragma once

#include "NodoCola.h"

template <class T>
class Cola {
    private:
        NodoCola<T>* primero;
        NodoCola<T>* ultimo;
        int largo;

    public:
        Cola() {
            this->primero = nullptr;
            this->ultimo = nullptr;
            this->largo = 0;
        }

        Cola(const Cola<T>&) = delete;
        Cola<T>& operator=(const Cola<T>&) = delete;

        void encolar(T dato) { 
            NodoCola<T>* nuevo = new NodoCola<T>(dato);
            if (estaVacia()) {
                primero = nuevo;
            } else {
                ultimo->setSiguiente(nuevo);
            }
            ultimo = nuevo;
            largo++;
        }

        T desencolar() {
            NodoCola<T>* aBorrar = primero;
            T dato = aBorrar->getDato();
            primero = primero->getSiguiente();
            if (primero == nullptr) {
                ultimo = nullptr;
            }
            delete aBorrar;
            largo--;
            return dato;
        }

        T verPrimero() { return primero->getDato(); }

        bool estaVacia() { return largo == 0; }

        int obtenerLargo() { return largo; }

        ~Cola() {
            while (!estaVacia()) {
                desencolar();
            }
        }
};
