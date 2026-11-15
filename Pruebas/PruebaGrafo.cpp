// Pruebas del grafo: camino minimo en tramos (BFS) e inexistencia de recorrido.
// Cubre los items A.6 y A.7 de la consigna.
// Compilar desde la carpeta Pruebas:
//   g++ -std=c++17 -Wall -Wextra PruebaGrafo.cpp -o pruebaGrafo
#include <iostream>
#include <string>

#include "../Estructuras/Grafo/Grafo.h"

static int fallas = 0;

static void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

static std::string caminoATexto(Lista<std::string>& camino) {
    std::string texto;
    NodoLista<std::string>* actual = camino.obtenerPrimero();

    while (actual != nullptr) {
        if (!texto.empty()) {
            texto += "->";
        }
        texto += actual->getDato();
        actual = actual->getSiguiente();
    }

    return texto;
}

int main() {
    Grafo<std::string> grafo(nullptr, 0);

    grafo.agregarVertice("PLZ");
    grafo.agregarVertice("CAB");
    grafo.agregarVertice("PAL");
    grafo.agregarVertice("RET");
    grafo.agregarVertice("CON");
    grafo.agregarVertice("BOE");
    grafo.agregarVertice("XXX");   // vertice aislado

    grafo.agregarArista("PLZ", "CAB");
    grafo.agregarArista("CAB", "PAL");
    grafo.agregarArista("PAL", "RET");
    grafo.agregarArista("RET", "CON");
    grafo.agregarArista("CON", "BOE");

    // Una arista con un extremo inexistente se ignora y no crea el vertice.
    grafo.agregarArista("PLZ", "ZZZ");
    verificar(!grafo.existeVertice("ZZZ"), "agregarArista no crea vertices");

    Lista<std::string> camino;
    int largo = -5;

    verificar(grafo.caminoMasCorto("PLZ", "RET", camino, largo), "hay camino PLZ -> RET");
    verificar(largo == 3, "PLZ -> RET tiene 3 tramos");
    verificar(caminoATexto(camino) == "PLZ->CAB->PAL->RET", "el camino PLZ -> RET es el correcto");
    verificar(camino.obtenerLargo() == 4, "el camino PLZ -> RET tiene 4 estaciones");

    verificar(grafo.caminoMasCorto("PLZ", "BOE", camino, largo), "hay camino PLZ -> BOE");
    verificar(largo == 5, "PLZ -> BOE tiene 5 tramos");
    verificar(caminoATexto(camino) == "PLZ->CAB->PAL->RET->CON->BOE",
              "el camino PLZ -> BOE es el correcto");

    verificar(grafo.caminoMasCorto("BOE", "PLZ", camino, largo), "el grafo es bidireccional");
    verificar(largo == 5 && caminoATexto(camino) == "BOE->CON->RET->PAL->CAB->PLZ",
              "el camino inverso BOE -> PLZ es el correcto");

    verificar(grafo.caminoMasCorto("PLZ", "PLZ", camino, largo), "origen igual a destino");
    verificar(largo == 0 && caminoATexto(camino) == "PLZ", "camino de 0 tramos");

    largo = -5;
    verificar(!grafo.caminoMasCorto("PLZ", "XXX", camino, largo),
              "no hay recorrido hacia un vertice aislado");
    verificar(largo == -1, "el largo queda en -1 cuando no hay recorrido");
    verificar(camino.estaVacia(), "el camino queda vacio cuando no hay recorrido");

    verificar(!grafo.caminoMasCorto("ZZZ", "PLZ", camino, largo), "origen inexistente devuelve false");
    verificar(!grafo.caminoMasCorto("PLZ", "ZZZ", camino, largo), "destino inexistente devuelve false");
    verificar(!grafo.caminoMasCorto("ZZZ", "ZZZ", camino, largo), "ambos inexistentes devuelve false");

    // Despues de una busqueda fallida el grafo tiene que seguir funcionando.
    verificar(grafo.caminoMasCorto("CAB", "RET", camino, largo), "el grafo se puede reutilizar");
    verificar(largo == 2 && caminoATexto(camino) == "CAB->PAL->RET",
              "el camino CAB -> RET es el correcto");

    // Al eliminar un vertice se eliminan sus aristas: PAL-RET-CON queda cortado.
    verificar(grafo.eliminarVertice("RET"), "se elimina el vertice RET");
    verificar(!grafo.existeVertice("RET"), "RET ya no existe");
    verificar(!grafo.caminoMasCorto("PAL", "CON", camino, largo),
              "sin RET ya no hay recorrido PAL -> CON");

    // Sin RET, PLZ y BOE quedan en componentes separadas.
    verificar(!grafo.caminoMasCorto("PLZ", "BOE", camino, largo),
              "sin RET no hay recorrido PLZ -> BOE");

    // Una arista directa nueva reconecta y deja el camino en 1 tramo.
    grafo.agregarArista("PLZ", "BOE");
    verificar(grafo.caminoMasCorto("PLZ", "BOE", camino, largo), "hay camino directo PLZ -> BOE");
    verificar(largo == 1 && caminoATexto(camino) == "PLZ->BOE",
              "la arista directa deja el camino en 1 tramo");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
