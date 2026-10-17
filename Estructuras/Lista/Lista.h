#pragma once

#include "NodoLista.h"

template <class T>
class Lista {
    private:
        NodoLista<T>* primero;
        int largo;

    public:
        Lista(NodoLista<T>* primero, int largo) {
            this->primero = primero;
            this->largo = largo;
        }

        void insertarEnPosicion(T dato, int posicion) {
            NodoLista<T>* nuevoNodo = new NodoLista<T>(dato, nullptr);
            if (posicion == 0) {
                nuevoNodo->setSiguiente(primero);
                primero = nuevoNodo;
            } else {
                NodoLista<T>* actual = primero;
                for (int i = 0; i < posicion - 1 && actual != nullptr; i++) {
                    actual = actual->getSiguiente();
                }
                if (actual != nullptr) {
                    nuevoNodo->setSiguiente(actual->getSiguiente());
                    actual->setSiguiente(nuevoNodo);
                }
            }
        }

        void insertarAlFinal(T dato) { 
            NodoLista<T>* nuevoNodo = new NodoLista<T>(dato, nullptr);
            if (primero == nullptr) {
                primero = nuevoNodo;
            } else {
                NodoLista<T>* actual = primero;
                while (actual->getSiguiente() != nullptr) {
                    actual = actual->getSiguiente();
                }
                actual->setSiguiente(nuevoNodo);
            }
        }

        void eliminarEnPosicion(int posicion) { 
            if (posicion == 0 && primero != nullptr) {
                NodoLista<T>* temp = primero;
                primero = primero->getSiguiente();
                delete temp;
            } else {
                NodoLista<T>* actual = primero;
                for (int i = 0; i < posicion - 1 && actual != nullptr; i++) {
                    actual = actual->getSiguiente();
                }
                if (actual != nullptr && actual->getSiguiente() != nullptr) {
                    NodoLista<T>* temp = actual->getSiguiente();
                    actual->setSiguiente(temp->getSiguiente());
                    delete temp;
                }
            }
        }

        T obtenerEnPosicion(int posicion) { 
            NodoLista<T>* actual = primero;
            for (int i = 0; i < posicion && actual != nullptr; i++) {
                actual = actual->getSiguiente();
            }
            if (actual != nullptr) {
                return actual->getDato();
            }
            return nullptr; 
        }

        bool estaVacia() { return primero == nullptr; }

        int obtenerLargo() { return largo; }

        ~Lista() {
            NodoLista<T>* actual = primero;
            while (actual != nullptr) {
                NodoLista<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
};
