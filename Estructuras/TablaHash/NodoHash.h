#pragma once

#include <string>

template <class V>
class NodoHash {
    private:
        std::string clave;
        V dato;
        NodoHash<V>* siguiente;

    public:
        NodoHash(std::string clave, V dato, NodoHash<V>* siguiente) {
            this->clave = clave;
            this->dato = dato;
            this->siguiente = siguiente;
        }

        std::string getClave() { return clave; }

        V getDato() { return dato; }

        NodoHash<V>* getSiguiente() { return siguiente; }

        void setSiguiente(NodoHash<V>* nodo) { siguiente = nodo; }
};
