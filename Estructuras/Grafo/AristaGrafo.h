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

        VerticeGrafo<T>* getDestino() { return nullptr; }

        AristaGrafo<T>* getSiguiente() { return nullptr; }

        void setSiguiente(AristaGrafo<T>* arista) { }
};
