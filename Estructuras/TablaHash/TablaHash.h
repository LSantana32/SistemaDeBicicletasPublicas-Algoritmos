#pragma once

#include <string>

#include "NodoHash.h"

template <class V>
class TablaHash
{
private:
    NodoHash<V> **tabla;
    int capacidad;
    int cantidad;
    int colisiones;

    int funcionHash(std::string clave)  //folding hash -> dividir la clave en partes y hacer xor entre ellas
    {
        if (capacidad <= 0)
        {
            return 0;
        }
        int parte1 = (unsigned char)clave[0]; //ascii
        int parte2 = ((unsigned char)clave[1] << 8) | (unsigned char)clave[2];  // caracter 2 * 256 + caracter 3
        int plegado = parte1 ^ parte2; //xor (diferencia de bits)
        return plegado % capacidad;
    }

public:
    TablaHash(int capacidad)
    {
        this->capacidad = capacidad;
        this->cantidad = 0;
        this->colisiones = 0;
        this->tabla = new NodoHash<V> *[capacidad];
        for (int i = 0; i < capacidad; i++)
        {
            this->tabla[i] = nullptr;
        }
    }

    bool insertar(std::string clave, V dato)  
    {
        if (capacidad <= 0 || tabla == nullptr)
        {
            return false;
        }
        int posicion = funcionHash(clave);
        if (tabla[posicion] == nullptr)
        {
            tabla[posicion] = new NodoHash<V>(clave, dato, nullptr);
            cantidad++;
            return true;
        }
        NodoHash<V> *actual = tabla[posicion];   
        while (actual != nullptr)
        {
            if (actual->getClave() == clave)
            {
                return false;
            }
            actual = actual->getSiguiente();
        }
        tabla[posicion] = new NodoHash<V>(clave, dato, tabla[posicion]);
        cantidad++;
        colisiones++;
        return true;
    }

    bool buscar(std::string clave, V &resultado)
    {
        if (capacidad <= 0 || tabla == nullptr)
        {
            return false;
        }
        int posicion = funcionHash(clave);
        NodoHash<V> *actual = tabla[posicion];
        while (actual != nullptr)
        {
            if (actual->getClave() == clave)
            {
                resultado = actual->getDato();
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    bool eliminar(std::string clave)
    {
        if (capacidad <= 0 || tabla == nullptr)
        {
            return false;
        }
        int posicion = funcionHash(clave);
        NodoHash<V> *actual = tabla[posicion];
        NodoHash<V> *anterior = nullptr;
        while (actual != nullptr)
        {
            if (actual->getClave() == clave)
            {
                if (anterior == nullptr)
                {
                    tabla[posicion] = actual->getSiguiente();
                }
                else
                {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                delete actual;
                cantidad--;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    void obtenerTodos(V *destino)
    {
        int k = 0;
        for (int i = 0; i < capacidad; i++)
        {
            NodoHash<V> *actual = tabla[i];
            while (actual != nullptr)
            {
                destino[k] = actual->getDato();
                k++;
                actual = actual->getSiguiente();
            }
        }
    }

    int obtenerCantidad() { return cantidad; }

    int obtenerColisiones() { return colisiones; }

    double calcularFactorDeCarga()
    {
        if (capacidad <= 0)
        {
            return 0.0;
        }
        return (double)cantidad / capacidad;
    }

    ~TablaHash()
    {
        for (int i = 0; i < capacidad; i++)
        {
            NodoHash<V> *actual = tabla[i];
            while (actual != nullptr)
            {
                NodoHash<V> *siguiente = actual->getSiguiente();
                delete actual;
                actual = siguiente;
            }
        }
        delete[] tabla;
    }
};
