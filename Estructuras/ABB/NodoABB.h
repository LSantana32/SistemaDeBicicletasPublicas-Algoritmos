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

        K getClave() { return clave; }

        V getDato() { return dato; }

        NodoABB<K, V>* getIzquierdo() { return izquierdo; }

        NodoABB<K, V>* getDerecho() { return derecho; }

        void setClave(K nuevaClave) { clave = nuevaClave; }

        void setDato(V nuevoDato) { dato = nuevoDato; }

        void setIzquierdo(NodoABB<K, V>* nodo) { izquierdo = nodo;}

        void setDerecho(NodoABB<K, V>* nodo) { derecho = nodo;}
};
