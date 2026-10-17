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

        void insertarEnPosicion(T dato, int posicion) { }

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

        void insertarLuegoDeEliminando(T dato, T datoAnterior) { 
            NodoLista<T>* actual = primero;
            while (actual != nullptr && actual->getDato() != datoAnterior) {
                actual = actual->getSiguiente();
            }
            if (actual != nullptr) {
                NodoLista<T>* nuevoNodo = new NodoLista<T>(dato, nullptr);
                actual->setSiguiente(nuevoNodo);
            }
        }

        void eliminarEnPosicion(int posicion) { }

        T obtenerEnPosicion(int posicion) { return T(); }

        bool estaVacia() { return false; }

        int obtenerLargo() { return 0; }

        ~Lista() { }
};
