#pragma once

#include "NodoABB.h"

template <class K, class V>
class ABB {
    private:
        NodoABB<K, V>* raiz;
        int cantidad;

        int alturaRecursiva(NodoABB<K, V>* nodo) { return 0; }

        void liberarPostorder(NodoABB<K, V>* nodo) { }

    public:
        ABB(NodoABB<K, V>* raiz, int cantidad) {
            this->raiz = raiz;
            this->cantidad = cantidad;
        }

        bool insertar(K clave, V dato) { return false; }

        bool buscar(K clave, V& resultado) { return false; }

        bool eliminar(K clave) { return false; }

        void obtenerEnInorder(V* destino) { }

        int calcularAltura() { return 0; }

        int obtenerCantidad() { return 0; }

        bool estaVacio() { return false; }

        ~ABB() { }
};
