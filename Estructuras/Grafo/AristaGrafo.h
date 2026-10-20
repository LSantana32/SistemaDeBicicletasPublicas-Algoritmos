#pragma once

template <class T>
class VerticeGrafo;

template <class T>
class AristaGrafo {
    private:
        VerticeGrafo<T>* destino;
        AristaGrafo<T>* siguiente;

    public:
        AristaGrafo(VerticeGrafo<T>* destino, AristaGrafo<T>* siguiente) {
            this->destino = destino;
            this->siguiente = siguiente;
        }

        VerticeGrafo<T>* getDestino() { return destino; }

        AristaGrafo<T>* getSiguiente() { return siguiente; }

        void setSiguiente(AristaGrafo<T>* arista) { siguiente = arista; }
};
