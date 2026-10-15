#pragma once

template <class T>
class NodoLista {
    private:
        T dato;
        NodoLista<T>* siguiente;

    public:
        NodoLista(T dato, NodoLista<T>* siguiente) {
            this->dato = dato;
            this->siguiente = siguiente;
        }

        T getDato() { return T(); }

        NodoLista<T>* getSiguiente() { return nullptr; }

        void setSiguiente(NodoLista<T>* nodo) { }
};
