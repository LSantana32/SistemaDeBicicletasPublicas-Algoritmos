#include <iostream>
#include <string>
#include "../Estructuras/HeapMin/HeapMin.h"

static int fallas = 0;

static void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

int main() {
    HeapMin<std::string> heap;
    verificar(heap.estaVacio(), "un heap nuevo esta vacio");
    verificar(heap.extraerMinimo() == "", "extraer de un heap vacio no rompe (devuelve vacio)");

    // Entran desordenadas: tienen que salir de la mas urgente (1) a la menos (3)
    heap.insertar("prioridad 3 (a)", 3);
    heap.insertar("prioridad 1 (a)", 1);
    heap.insertar("prioridad 2", 2);
    heap.insertar("prioridad 3 (b)", 3);
    heap.insertar("prioridad 1 (b)", 1);
    verificar(heap.obtenerCantidad() == 5, "despues de 5 insertar hay 5");
    verificar(heap.verMinimo().find("prioridad 1") == 0, "verMinimo muestra uno de prioridad 1");
    verificar(heap.obtenerCantidad() == 5, "verMinimo no saca nada");

    verificar(heap.extraerMinimo().find("prioridad 1") == 0, "sale primero uno de prioridad 1");
    verificar(heap.extraerMinimo().find("prioridad 1") == 0, "despues el otro de prioridad 1");
    verificar(heap.extraerMinimo() == "prioridad 2", "despues el de prioridad 2");
    verificar(heap.extraerMinimo().find("prioridad 3") == 0, "despues uno de prioridad 3");
    verificar(heap.extraerMinimo().find("prioridad 3") == 0, "y al final el otro de prioridad 3");
    verificar(heap.estaVacio(), "queda vacio");

    // Arranca con lugar para 10: con 25 tiene que agrandar el arreglo dos veces
    HeapMin<int> numeros;
    for (int i = 25; i >= 1; i--) {
        numeros.insertar(i * 100, i % 3 + 1);   // prioridades 1, 2 y 3 mezcladas
    }
    verificar(numeros.obtenerCantidad() == 25, "entran 25 aunque la capacidad inicial es 10");

    bool enOrden = true;
    int anterior = 0;
    int extraidos = 0;
    while (!numeros.estaVacio()) {
        int dato = numeros.extraerMinimo();
        int prioridad = (dato / 100) % 3 + 1;   // la misma cuenta que al insertar
        if (prioridad < anterior) {
            enOrden = false;
        }
        anterior = prioridad;
        extraidos++;
    }
    verificar(enOrden && extraidos == 25, "los 25 salen ordenados por prioridad");

    // Queda con elementos adentro: el destructor tiene que liberar el arreglo
    numeros.insertar(7, 2);
    numeros.insertar(8, 1);

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
