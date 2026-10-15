#pragma once

#include "NodoLista.h"

template <class T>
class Lista {
    private:
        NodoLista<T>* primero;
        int largo;

    public:
        Lista(NodoLista<T>* primero, int largo) {
            this->primero = primero;
            this->largo = largo;
        }

        void insertarEnPosicion(T dato, int posicion) { }

        void eliminarEnPosicion(int posicion) { }

        T obtenerEnPosicion(int posicion) { return T(); }

        bool estaVacia() { return false; }

        int obtenerLargo() { return 0; }

        ~Lista() { }
};
