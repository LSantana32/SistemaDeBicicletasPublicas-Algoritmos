#pragma once

#include "ElementoHeap.h"

template <class T>
class HeapMin {
    private:
        ElementoHeap<T>* elementos;
        int cantidad;
        int capacidad;

        void subirElemento(int posicion) { }

        void bajarElemento(int posicion) { }

        void agrandarArreglo() { }

    public:
        HeapMin(ElementoHeap<T>* elementos, int cantidad, int capacidad) {
            this->elementos = elementos;
            this->cantidad = cantidad;
            this->capacidad = capacidad;
        }

        void insertar(T dato, int prioridad) { }

        T extraerMinimo() { return T(); }

        T verMinimo() { return T(); }

        bool estaVacio() { return false; }

        int obtenerCantidad() { return 0; }

        ~HeapMin() { }
};
