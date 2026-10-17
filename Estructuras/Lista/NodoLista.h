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

        T getDato() { 
            return dato;
        }

        NodoLista<T>* getSiguiente() {
            return siguiente; 
        }

        void setSiguiente(NodoLista<T>* nodo) {
            siguiente = nodo;
        }
};
