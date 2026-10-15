#pragma once

#include "VerticeGrafo.h"

template <class T>
class Grafo {
    private:
        VerticeGrafo<T>* primerVertice;
        int cantidadVertices;

        VerticeGrafo<T>* buscarVertice(T dato) { return nullptr; }

        void reiniciarMarcas() { }

    public:
        Grafo(VerticeGrafo<T>* primerVertice, int cantidadVertices) {
            this->primerVertice = primerVertice;
            this->cantidadVertices = cantidadVertices;
        }

        void agregarVertice(T dato) { }

        bool eliminarVertice(T dato) { return false; }

        void agregarArista(T origen, T destino) { }

        bool existeVertice(T dato) { return false; }

        bool caminoMasCorto(T origen, T destino, T* camino, int& largo) { return false; }

        ~Grafo() { }
};
