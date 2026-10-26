#pragma once

#include "ElementoHeap.h"

template <class T>
class HeapMin {
    private:
        ElementoHeap<T>* elementos;
        int cantidad;
        int capacidad;

        void subirElemento(int posicion) {  
            bool enSuLugar = false;
            while (posicion > 0 && !enSuLugar) {
                int padre = (posicion - 1) / 2;
                if (elementos[posicion].getPrioridad() < elementos[padre].getPrioridad()) {
                    ElementoHeap<T> aux = elementos[posicion];
                    elementos[posicion] = elementos[padre];
                    elementos[padre] = aux;
                    posicion = padre;
                } else {
                    enSuLugar = true;
                }
            }
        }

        void bajarElemento(int posicion) { 
            bool enSuLugar = false;
            while (2 * posicion + 1 < cantidad && !enSuLugar) {
                int izquierdo = 2 * posicion + 1;
                int derecho = 2 * posicion + 2;
                int menor = posicion;

                if (izquierdo < cantidad &&
                    elementos[izquierdo].getPrioridad() < elementos[menor].getPrioridad()) {
                    menor = izquierdo;
                }

                if (derecho < cantidad &&
                    elementos[derecho].getPrioridad() < elementos[menor].getPrioridad()) {
                    menor = derecho;
                }
        
                if (menor == posicion) {
                    enSuLugar = true;   
                } else {
                    ElementoHeap<T> aux = elementos[posicion];
                    elementos[posicion] = elementos[menor];
                    elementos[menor] = aux;
                    posicion = menor;
                }
            }
        }

        void agrandarArreglo() { 
            int nuevaCapacidad = capacidad * 2;
            ElementoHeap<T>* nuevo = new ElementoHeap<T>[nuevaCapacidad];
            for (int i = 0; i < cantidad; i++) {
                nuevo[i] = elementos[i];
            }
            delete[] elementos;
            elementos = nuevo;
            capacidad = nuevaCapacidad;
        }

    public:
        HeapMin() {
            this->capacidad = 10;
            this->cantidad = 0;
            this->elementos = new ElementoHeap<T>[capacidad];
        }

        HeapMin(const HeapMin<T>&) = delete;
        HeapMin<T>& operator=(const HeapMin<T>&) = delete;

        void insertar(T dato, int prioridad) { 
            if (cantidad == capacidad) {
                agrandarArreglo();
            }
            elementos[cantidad] = ElementoHeap<T>(dato, prioridad);   // va al final...
            cantidad++;
            subirElemento(cantidad - 1);
        }

        T extraerMinimo() {
            if (estaVacio()) {
                return T();
            }
            T minimo = elementos[0].getDato();   
            cantidad--;
            elementos[0] = elementos[cantidad];  
            bajarElemento(0);                  
            return minimo;
        }

        T verMinimo() {
            if (estaVacio()) {
                return T();
            }
            return elementos[0].getDato();
        }

        bool estaVacio() { return cantidad == 0;  }

        int obtenerCantidad() { return cantidad; }

        ~HeapMin() { 
            delete[] elementos;
        }
};
