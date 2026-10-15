#pragma once

template <class K, class V>
class NodoABB {
    private:
        K clave;
        V dato;
        NodoABB<K, V>* izquierdo;
        NodoABB<K, V>* derecho;

    public:
        NodoABB(K clave, V dato, NodoABB<K, V>* izquierdo, NodoABB<K, V>* derecho) {
            this->clave = clave;
            this->dato = dato;
            this->izquierdo = izquierdo;
            this->derecho = derecho;
        }

        K getClave() { return K(); }

        V getDato() { return V(); }

        NodoABB<K, V>* getIzquierdo() { return nullptr; }

        NodoABB<K, V>* getDerecho() { return nullptr; }

        void setIzquierdo(NodoABB<K, V>* nodo) { }

        void setDerecho(NodoABB<K, V>* nodo) { }
};
