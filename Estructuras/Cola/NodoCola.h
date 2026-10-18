#pragma once

template <class T>
class NodoCola {
    private:
        T dato;
        NodoCola<T>* siguiente;

    public:
        NodoCola(T dato) {
            this->dato = dato;
            this->siguiente = nullptr;
        }

        T getDato() { return dato; }

        NodoCola<T>* getSiguiente() { return siguiente; }

        void setSiguiente(NodoCola<T>* nodo) { siguiente = nodo; }
};
