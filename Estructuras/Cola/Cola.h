#pragma once

#include "NodoCola.h"

template <class T>
class Cola {
    private:
        NodoCola<T>* primero;
        NodoCola<T>* ultimo;
        int largo;

    public:
        Cola(NodoCola<T>* primero, NodoCola<T>* ultimo, int largo) {
            this->primero = primero;
            this->ultimo = ultimo;
            this->largo = largo;
        }

        void encolar(T dato) { }

        T desencolar() { return T(); }

        T verPrimero() { return T(); }

        bool estaVacia() { return false; }

        int obtenerLargo() { return 0; }

        ~Cola() { }
};
