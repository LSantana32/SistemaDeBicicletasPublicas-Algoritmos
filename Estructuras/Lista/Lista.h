#pragma once

#include "NodoLista.h"

template <class T>
class Lista {
    private:
        NodoLista<T>* primero;
        int largo;

    public:
        Lista() {
            this->primero = nullptr;
            this->largo = 0;
        }

        Lista(NodoLista<T>* primero, int largo) {
            this->primero = primero;
            this->largo = largo;
        }

        void vaciar() {
            NodoLista<T>* actual = primero;
            while (actual != nullptr) {
                NodoLista<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
            primero = nullptr;
            largo = 0;
        }

        NodoLista<T>* obtenerPrimero() {
            return primero;
        }

        void insertarEnPosicion(T dato, int posicion) {
            if (posicion < 0) {
                return;
            }

            if (posicion >= largo || primero == nullptr) {
                insertarAlFinal(dato);
                return;
            }

            NodoLista<T>* nuevoNodo = new NodoLista<T>(dato, nullptr);

            if (posicion == 0) {
                nuevoNodo->setSiguiente(primero);
                primero = nuevoNodo;
            } else {
                NodoLista<T>* actual = primero;
                for (int i = 0; i < posicion - 1; i++) {
                    actual = actual->getSiguiente();
                }
                nuevoNodo->setSiguiente(actual->getSiguiente());
                actual->setSiguiente(nuevoNodo);
            }

            largo++;
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

            largo++;
        }

        void eliminarEnPosicion(int posicion) {
            if (posicion < 0 || posicion >= largo || primero == nullptr) {
                return;
            }

            if (posicion == 0) {
                NodoLista<T>* temp = primero;
                primero = primero->getSiguiente();
                delete temp;
            } else {
                NodoLista<T>* actual = primero;
                for (int i = 0; i < posicion - 1; i++) {
                    actual = actual->getSiguiente();
                }

                NodoLista<T>* temp = actual->getSiguiente();
                actual->setSiguiente(temp->getSiguiente());
                delete temp;
            }

            largo--;
        }

        T obtenerEnPosicion(int posicion) {
            if (posicion < 0 || posicion >= largo) {
                return T();
            }

            NodoLista<T>* actual = primero;
            for (int i = 0; i < posicion && actual != nullptr; i++) {
                actual = actual->getSiguiente();
            }

            if (actual != nullptr) {
                return actual->getDato();
            }

            return T();
        }

        bool estaVacia() const { return primero == nullptr; }

        int obtenerLargo() const { return largo; }

        ~Lista() {
            vaciar();
        }
};
