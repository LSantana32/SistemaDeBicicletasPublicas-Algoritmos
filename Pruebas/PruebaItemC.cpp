// Pruebas del registro de bicicletas con ABB (item C).
// Cubre insercion, busqueda, recorrido inorder, altura, conteo de averiadas,
// liberacion postorder y eliminacion en los tres casos.
// Compilar desde la raiz del proyecto:
//   g++ -std=c++17 -Wall -Wextra Pruebas/PruebaItemC.cpp -o pruebaItemC
#include <iostream>
#include <sstream>
#include <string>

#include "../Estructuras/ABB/ABB.h"
#include "../Sistema/SistemaBicis.h"

static int fallas = 0;
static int datosDestruidos = 0;

static void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

template <class Funcion>
static std::string capturarSalida(Funcion funcion) {
    std::ostringstream salida;
    std::streambuf* original = std::cout.rdbuf(salida.rdbuf());
    funcion();
    std::cout.rdbuf(original);
    return salida.str();
}

struct DatoPrueba {
    int id;

    explicit DatoPrueba(int id) {
        this->id = id;
    }

    ~DatoPrueba() {
        datosDestruidos++;
    }
};

static void cargarArbol(ABB<int, DatoPrueba*>& arbol, const int* ids, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        arbol.insertar(ids[i], new DatoPrueba(ids[i]));
    }
}

static bool tieneId(ABB<int, DatoPrueba*>& arbol, int id) {
    DatoPrueba* encontrado = nullptr;
    return arbol.buscar(id, encontrado)
        && encontrado != nullptr
        && encontrado->id == id;
}

static bool inorderEsperado(ABB<int, DatoPrueba*>& arbol,
                            const int* esperados, int cantidad) {
    DatoPrueba** destino = new DatoPrueba*[cantidad];
    arbol.obtenerEnInorder(destino);

    bool correcto = true;
    for (int i = 0; i < cantidad; i++) {
        if (destino[i] == nullptr || destino[i]->id != esperados[i]) {
            correcto = false;
        }
    }

    delete[] destino;
    return correcto;
}

int main() {
    std::cout << "=== ABB: insercion, busqueda e inorder ===\n";

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80};
        cargarArbol(arbol, ids, 7);

        verificar(arbol.obtenerCantidad() == 7, "insertar agrega los siete nodos");
        verificar(tieneId(arbol, 40), "buscar encuentra una bicicleta existente");

        DatoPrueba* noExiste = nullptr;
        verificar(!arbol.buscar(99, noExiste) && noExiste == nullptr,
                  "buscar devuelve false para un ID inexistente");

        int esperados[] = {20, 30, 40, 50, 60, 70, 80};
        verificar(inorderEsperado(arbol, esperados, 7),
                  "el recorrido inorder devuelve los IDs ordenados");

        DatoPrueba* duplicado = new DatoPrueba(50);
        verificar(!arbol.insertar(50, duplicado),
                  "insertar rechaza un ID duplicado");
        verificar(arbol.obtenerCantidad() == 7,
                  "el ID duplicado no incrementa la cantidad");
        delete duplicado;

        verificar(!arbol.eliminar(99), "eliminar devuelve false para un ID inexistente");
        verificar(arbol.obtenerCantidad() == 7,
                  "una eliminacion inexistente no cambia la cantidad");
    }
    verificar(datosDestruidos == 8,
              "el ABB libera sus datos y el duplicado rechazado lo libera el llamador");

    std::cout << "\n=== ABB: altura ===\n";

    {
        ABB<int, DatoPrueba*> vacio(nullptr, 0);
        verificar(vacio.calcularAltura() == 0, "la altura de un arbol vacio es 0");

        vacio.insertar(10, new DatoPrueba(10));
        verificar(vacio.calcularAltura() == 1, "la altura de un unico nodo es 1");
    }

    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80};
        cargarArbol(arbol, ids, 7);
        verificar(arbol.calcularAltura() == 3,
                  "la altura del arbol balanceado es 3");
    }

    std::cout << "\n=== ABB: eliminacion ===\n";

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80};
        cargarArbol(arbol, ids, 7);

        verificar(arbol.eliminar(20), "eliminar una hoja devuelve true");
        verificar(!tieneId(arbol, 20), "la hoja eliminada ya no se encuentra");
        verificar(arbol.obtenerCantidad() == 6,
                  "eliminar una hoja descuenta un nodo");

        int esperados[] = {30, 40, 50, 60, 70, 80};
        verificar(inorderEsperado(arbol, esperados, 6),
                  "el inorder sigue ordenado tras eliminar una hoja");
    }
    verificar(datosDestruidos == 7,
              "eliminar una hoja libera su dato y el destructor libera el resto");

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80, 65};
        cargarArbol(arbol, ids, 8);

        verificar(arbol.eliminar(60), "eliminar un nodo con un hijo devuelve true");
        verificar(!tieneId(arbol, 60), "el nodo con un hijo ya no se encuentra");
        verificar(tieneId(arbol, 65), "el hijo del nodo eliminado se conserva");
        verificar(arbol.obtenerCantidad() == 7,
                  "eliminar un nodo con un hijo descuenta un nodo");

        int esperados[] = {20, 30, 40, 50, 65, 70, 80};
        verificar(inorderEsperado(arbol, esperados, 7),
                  "el inorder sigue ordenado tras eliminar un nodo con un hijo");
    }
    verificar(datosDestruidos == 8,
              "eliminar un nodo con un hijo libera su dato y el destructor libera el resto");

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80};
        cargarArbol(arbol, ids, 7);

        verificar(arbol.eliminar(30), "eliminar un nodo con dos hijos devuelve true");
        verificar(!tieneId(arbol, 30), "el nodo con dos hijos ya no se encuentra");
        verificar(tieneId(arbol, 40), "el sucesor inorder queda en el arbol");
        verificar(arbol.obtenerCantidad() == 6,
                  "eliminar un nodo con dos hijos descuenta un nodo");

        int esperados[] = {20, 40, 50, 60, 70, 80};
        verificar(inorderEsperado(arbol, esperados, 6),
                  "el inorder sigue ordenado tras eliminar un nodo con dos hijos");
    }
    verificar(datosDestruidos == 7,
              "eliminar un nodo con dos hijos libera su dato y el destructor libera el resto");

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {50, 30, 70, 20, 40, 60, 80};
        cargarArbol(arbol, ids, 7);

        verificar(arbol.eliminar(50), "eliminar la raiz con dos hijos devuelve true");
        verificar(!tieneId(arbol, 50), "la raiz eliminada ya no se encuentra");
        verificar(tieneId(arbol, 60), "el sucesor de la raiz queda en el arbol");

        int esperados[] = {20, 30, 40, 60, 70, 80};
        verificar(inorderEsperado(arbol, esperados, 6),
                  "el inorder sigue ordenado tras eliminar la raiz");
    }
    verificar(datosDestruidos == 7,
              "eliminar la raiz libera su dato y el destructor libera el resto");

    std::cout << "\n=== ABB: liberacion postorder ===\n";

    datosDestruidos = 0;
    {
        ABB<int, DatoPrueba*> arbol(nullptr, 0);
        int ids[] = {40, 20, 60, 10};
        cargarArbol(arbol, ids, 4);
        verificar(arbol.obtenerCantidad() == 4, "el arbol tiene cuatro datos antes de destruirse");
    }
    verificar(datosDestruidos == 4,
              "el destructor libera todos los datos del arbol");

    std::cout << "\n=== SistemaBicis: funcionalidades del item C ===\n";

    SistemaBicis sistema;
    sistema.agregarEstacion(new Estacion("TST", "Test", "Centro", 10, 4));
    sistema.agregarBicicleta(2, "TST", "Mecanica", "OK", 100);
    sistema.agregarBicicleta(1, "TST", "Mecanica", "Averiada", 200);
    sistema.agregarBicicleta(3, "TST", "Electrica", "Averiada", 300);
    sistema.agregarBicicleta(4, "TST", "Mecanica", "OK", 400);

    Bicicleta* bici3 = sistema.buscarBicicletaPorId(3);
    verificar(bici3 != nullptr && bici3->getId() == 3,
              "buscarBicicletaPorId encuentra una bicicleta del sistema");
    verificar(sistema.buscarBicicletaPorId(99) == nullptr,
              "buscarBicicletaPorId devuelve nullptr para un ID inexistente");

    verificar(sistema.contarBicicletasAveriadas() == 2,
              "contarBicicletasAveriadas cuenta las bicicletas averiadas");

    std::string listado = capturarSalida([&sistema]() {
        sistema.listarBicicletasOrdenadasPorId();
    });
    size_t pos1 = listado.find("ID: 1");
    size_t pos2 = listado.find("ID: 2");
    size_t pos3 = listado.find("ID: 3");
    size_t pos4 = listado.find("ID: 4");
    verificar(pos1 != std::string::npos && pos2 != std::string::npos
                  && pos3 != std::string::npos && pos4 != std::string::npos
                  && pos1 < pos2 && pos2 < pos3 && pos3 < pos4,
              "listarBicicletasOrdenadasPorId respeta el orden inorder");

    std::string altura = capturarSalida([&sistema]() {
        sistema.mostrarAlturaDelArbol();
    });
    verificar(altura.find("Altura del arbol de bicicletas: 3") != std::string::npos,
              "mostrarAlturaDelArbol informa la altura del ABB");

    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}
