#pragma once

template <class T>
class ElementoHeap {
    private:
        T dato;
        int prioridad;

    public:

        ElementoHeap() : dato(), prioridad(0) {}

        ElementoHeap(T dato, int prioridad) {
            this->dato = dato;
            this->prioridad = prioridad;
        }

        T getDato() { return dato; }

        int getPrioridad() { return prioridad; }
};
