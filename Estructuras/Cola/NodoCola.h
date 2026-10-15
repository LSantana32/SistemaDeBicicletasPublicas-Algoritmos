#pragma once

template <class T>
class NodoCola {
    private:
        T dato;
        NodoCola<T>* siguiente;

    public:
        NodoCola(T dato, NodoCola<T>* siguiente) {
            this->dato = dato;
            this->siguiente = siguiente;
        }

        T getDato() { return T(); }

        NodoCola<T>* getSiguiente() { return nullptr; }

        void setSiguiente(NodoCola<T>* nodo) { }
};
