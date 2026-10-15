#pragma once

template <class T>
class ElementoHeap {
    private:
        T dato;
        int prioridad;

    public:
        ElementoHeap(T dato, int prioridad) {
            this->dato = dato;
            this->prioridad = prioridad;
        }

        T getDato() { return T(); }

        int getPrioridad() { return 0; }
};
