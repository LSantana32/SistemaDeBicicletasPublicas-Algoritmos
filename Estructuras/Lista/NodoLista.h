#pragma once

template <class T>
class NodoLista {
    private:
        T dato;
        NodoLista<T>* siguiente;

    public:
        NodoLista(T dato, NodoLista<T>* siguiente = nullptr)
            : dato(dato), siguiente(siguiente) {
        }

        T getDato() const {
            return dato;
        }

        NodoLista<T>* getSiguiente() const {
            return siguiente;
        }

        void setSiguiente(NodoLista<T>* nodo) {
            siguiente = nodo;
        }
};
