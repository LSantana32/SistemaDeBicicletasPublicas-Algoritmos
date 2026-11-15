#pragma once

#include <string>

#include "NodoABB.h"

template <class K, class V>
class ABB {
    private:
        NodoABB<K, V>* raiz;
        int cantidad;

        NodoABB<K, V>* insertarRecursivo(
            NodoABB<K, V>* nodo, K clave, V dato, bool& insertado) {

            if (nodo == nullptr) {
                insertado = true;
                return new NodoABB<K, V>(clave, dato, nullptr, nullptr);
            }

            if (clave < nodo->getClave()) {
                nodo->setIzquierdo(
                    insertarRecursivo(nodo->getIzquierdo(),
                                        clave, dato, insertado));
            } else if (clave > nodo->getClave()) {
                nodo->setDerecho(
                    insertarRecursivo(nodo->getDerecho(),
                                        clave, dato, insertado));
            }

            return nodo;
        }

        NodoABB<K, V>* buscarRecursivo(
            NodoABB<K, V>* nodo, K clave) {

            if (nodo == nullptr || nodo->getClave() == clave) {
                return nodo;
            }

            if (clave < nodo->getClave()) {
                return buscarRecursivo(nodo->getIzquierdo(), clave);
            }

            return buscarRecursivo(nodo->getDerecho(), clave);
        }


        int alturaRecursiva(NodoABB<K, V>* nodo) {
            if (nodo == nullptr) {
                return 0;
            }

            int alturaIzquierda = alturaRecursiva(nodo->getIzquierdo());
            int alturaDerecha = alturaRecursiva(nodo->getDerecho());

            return 1 + (alturaIzquierda > alturaDerecha
                        ? alturaIzquierda : alturaDerecha);
        }

        void liberarPostorder(NodoABB<K, V>* nodo) {
            if (nodo == nullptr) {
                return;
            }

            liberarPostorder(nodo->getIzquierdo());
            liberarPostorder(nodo->getDerecho());
            delete nodo->getDato();
            delete nodo;
        }

        
        void inorderRecursivo(NodoABB<K, V>* nodo, V* destino, int& indice) {
            if (nodo == nullptr) {
                return;
            }

            inorderRecursivo(nodo->getIzquierdo(), destino, indice);
            destino[indice] = nodo->getDato();
            indice++;
            inorderRecursivo(nodo->getDerecho(), destino, indice);
        }


        V obtenerBicicletaDisponibleEnEstacionRecursivo(
            NodoABB<K, V>* nodo, std::string clave) {
            if (nodo == nullptr) {
                return nullptr;
            }

            V bicicleta = nodo->getDato();
            if (bicicleta != nullptr
                && bicicleta->getCodigoEstacion() == clave
                && !bicicleta->estaAveriada()) {
                return bicicleta;
            }

            V izquierda = obtenerBicicletaDisponibleEnEstacionRecursivo(nodo->getIzquierdo(), clave);
            if (izquierda != nullptr) {
                return izquierda;
            }

            return obtenerBicicletaDisponibleEnEstacionRecursivo(nodo->getDerecho(), clave);
        }

        NodoABB<K, V>* obtenerMinimo(NodoABB<K, V>* nodo) {
            while (nodo->getIzquierdo() != nullptr) {
                nodo = nodo->getIzquierdo();
            }

            return nodo;
        }

        // Elimina el nodo minimo del subarbol y devuelve su nueva raiz.
        NodoABB<K, V>* eliminarMinimo(NodoABB<K, V>* nodo) {
            if (nodo->getIzquierdo() == nullptr) {
                NodoABB<K, V>* derecho = nodo->getDerecho();
                delete nodo;
                return derecho;
            }

            nodo->setIzquierdo(eliminarMinimo(nodo->getIzquierdo()));
            return nodo;
        }

        NodoABB<K, V>* eliminarRecursivo(
            NodoABB<K, V>* nodo, K clave, bool& eliminado) {

            if (nodo == nullptr) {
                return nullptr;
            }

            if (clave < nodo->getClave()) {
                nodo->setIzquierdo(
                    eliminarRecursivo(nodo->getIzquierdo(), clave, eliminado));
                return nodo;
            }

            if (clave > nodo->getClave()) {
                nodo->setDerecho(
                    eliminarRecursivo(nodo->getDerecho(), clave, eliminado));
                return nodo;
            }

            eliminado = true;

            // Caso 1: nodo hoja
            if (nodo->getIzquierdo() == nullptr
                && nodo->getDerecho() == nullptr) {
                delete nodo->getDato();
                delete nodo;
                return nullptr;
            }

            // Caso 2: nodo con un solo hijo
            if (nodo->getIzquierdo() == nullptr
                || nodo->getDerecho() == nullptr) {
                NodoABB<K, V>* hijo = nodo->getIzquierdo() != nullptr
                    ? nodo->getIzquierdo() : nodo->getDerecho();

                delete nodo->getDato();
                delete nodo;
                return hijo;
            }

            // Caso 3: nodo con dos hijos. Se reemplaza por su sucesor inorder
            NodoABB<K, V>* sucesor = obtenerMinimo(nodo->getDerecho());
            nodo->setClave(sucesor->getClave());
            nodo->setDato(sucesor->getDato());
            nodo->setDerecho(eliminarMinimo(nodo->getDerecho()));

            return nodo;
        }

    public:
        ABB(NodoABB<K,V>* raiz, int cantidad) {
            this->raiz = raiz;
            this->cantidad = cantidad;
        }

        bool insertar(K clave, V dato) {
            bool insertado = false;
            raiz = insertarRecursivo(raiz, clave, dato, insertado);

            if (insertado) {
                cantidad++;
            }

            return insertado;
        }

        bool buscar(K clave, V& resultado) {
            NodoABB<K, V>* nodo = buscarRecursivo(raiz, clave);

            if (nodo == nullptr) {
                return false;
            }

            resultado = nodo->getDato();
            return true;
        }

        bool eliminar(K clave) {
            bool eliminado = false;
            raiz = eliminarRecursivo(raiz, clave, eliminado);

            if (eliminado) {
                cantidad--;
            }

            return eliminado;
        }

        void obtenerEnInorder(V* destino) {
            if(destino == nullptr){
                return;
            }
            int indice = 0;
            inorderRecursivo(raiz, destino, indice);
        }

        int calcularAltura() { return alturaRecursiva(raiz); }

        int obtenerCantidad() { return cantidad; }

        V obtenerBicicletaDisponibleEnEstacion(std::string clave) {
            V resultado = obtenerBicicletaDisponibleEnEstacionRecursivo(raiz, clave);
            if (resultado != nullptr) {
                return resultado;
            }
            return nullptr;
        }

        bool estaVacio() { return raiz == nullptr; }

        ~ABB() { liberarPostorder(raiz);}
};
