#pragma once

#include <string>

#include "NodoHash.h"

template <class V>
class TablaHash {
    private:
        NodoHash<V>** tabla;
        int capacidad;
        int cantidad;
        int colisiones;

        int funcionHash(std::string clave) { return 0; }

    public:
        TablaHash(NodoHash<V>** tabla, int capacidad, int cantidad, int colisiones) {
            this->tabla = tabla;
            this->capacidad = capacidad;
            this->cantidad = cantidad;
            this->colisiones = colisiones;
        }

        bool insertar(std::string clave, V dato) { return false; }

        bool buscar(std::string clave, V& resultado) { return false; }

        bool eliminar(std::string clave) { return false; }

        void obtenerTodos(V* destino) { }

        int obtenerCantidad() { return 0; }

        int obtenerColisiones() { return 0; }

        double calcularFactorDeCarga() { return 0.0; }

        ~TablaHash() { }
};
