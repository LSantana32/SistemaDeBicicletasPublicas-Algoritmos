# Plan — Estructura del proyecto (header-only)

Sistema de Bicicletas Públicas (C++17, POO). Skeleton basado en `Diagrama_de_clases_Bicicletas_v6.pdf`.

## Decisiones

- **Header-only**: cada clase en un único `.h` con métodos vacíos inline.
- **Constructor**: con parámetros, asigna cada atributo en el cuerpo.
- **Métodos**: todos vacíos, con retorno por defecto (`void` → nada, `int` → `0`, `double` → `0.0`, `bool` → `false`, puntero → `nullptr`, `std::string` → `std::string()`, template `T`/`V`/`K` → `T()`).
- **Destructores**: solo donde el UML los declara, cuerpo vacío.
- `#pragma once`, `std::string`, sin librerías extra.

## Estructura de carpetas

```
TP Segundo Q/
├─ main.cpp
├─ plan.md
├─ Estructuras/
│  ├─ Lista/          Lista.h, NodoLista.h
│  ├─ Cola/           Cola.h, NodoCola.h
│  ├─ Grafo/          Grafo.h, VerticeGrafo.h, AristaGrafo.h
│  ├─ ABB/            ABB.h, NodoABB.h
│  ├─ HeapMin/        HeapMin.h, ElementoHeap.h
│  ├─ TablaHash/      TablaHash.h, NodoHash.h
│  └─ Redistribuidor/ Redistribuidor.h
├─ Dominio/           Estacion.h, Bicicleta.h, Viaje.h
├─ Sistema/           Menu.h, SistemaBicis.h
└─ Archivos/          .gitkeep
```

## Clases y archivos

### main.cpp
`#include "Sistema/Menu.h"` → `int main() { Menu menu(nullptr); menu.iniciarMenu(); return 0; }`

### Estructuras/Lista/
- **NodoLista.h** `NodoLista<T>`: `-dato: T`, `-siguiente: NodoLista<T>*`. ctor `(T dato, NodoLista<T>* siguiente)`. Métodos: `getDato`, `getSiguiente`, `setSiguiente`.
- **Lista.h** `Lista<T>`: `-primero: NodoLista<T>*`, `-largo: int`. ctor `(NodoLista<T>* primero, int largo)`, `~Lista()`. Métodos: `insertarEnPosicion`, `eliminarEnPosicion`, `obtenerEnPosicion`, `estaVacia`, `obtenerLargo`.

### Estructuras/Cola/
- **NodoCola.h** `NodoCola<T>`: `-dato: T`, `-siguiente: NodoCola<T>*`. ctor `(T dato, NodoCola<T>* siguiente)`. Métodos: `getDato`, `getSiguiente`, `setSiguiente`.
- **Cola.h** `Cola<T>`: `-primero`, `-ultimo: NodoCola<T>*`, `-largo: int`. ctor `(NodoCola<T>* primero, NodoCola<T>* ultimo, int largo)`, `~Cola()`. Métodos: `encolar`, `desencolar`, `verPrimero`, `estaVacia`, `obtenerLargo`.

### Estructuras/Grafo/
- **AristaGrafo.h** `AristaGrafo<T>` (forward decl `VerticeGrafo<T>`): `-destino: VerticeGrafo<T>*`, `-siguiente: AristaGrafo<T>*`. ctor `(VerticeGrafo<T>* destino, AristaGrafo<T>* siguiente)`. Métodos: `getDestino`, `getSiguiente`, `setSiguiente`.
- **VerticeGrafo.h** `VerticeGrafo<T>`: `-dato: T`, `-primeraArista: AristaGrafo<T>*`, `-siguiente: VerticeGrafo<T>*`, `-visitado: bool`, `-anterior: VerticeGrafo<T>*`. ctor con los 5, `~VerticeGrafo()`. Métodos: `getDato`, `agregarAristaHacia`, `eliminarAristaHacia`, `getPrimeraArista`.
- **Grafo.h** `Grafo<T>`: `-primerVertice: VerticeGrafo<T>*`, `-cantidadVertices: int`. ctor con ambos, `~Grafo()`. Métodos: `agregarVertice`, `eliminarVertice`, `agregarArista`, `existeVertice`, `caminoMasCorto`, `buscarVertice`, `reiniciarMarcas`.

### Estructuras/ABB/
- **NodoABB.h** `NodoABB<K,V>`: `-clave: K`, `-dato: V`, `-izquierdo`, `-derecho: NodoABB<K,V>*`. ctor con los 4. Métodos: `getClave`, `getDato`, `getIzquierdo`, `getDerecho`, `setIzquierdo`, `setDerecho`.
- **ABB.h** `ABB<K,V>`: `-raiz: NodoABB<K,V>*`, `-cantidad: int`. ctor con ambos, `~ABB()`. Métodos: `insertar`, `buscar`, `eliminar`, `obtenerEnInorder`, `calcularAltura`, `obtenerCantidad`, `estaVacio`, `alturaRecursiva`, `liberarPostorder`.

### Estructuras/HeapMin/
- **ElementoHeap.h** `ElementoHeap<T>`: `-dato: T`, `-prioridad: int`. ctor `(T dato, int prioridad)`. Métodos: `getDato`, `getPrioridad`.
- **HeapMin.h** `HeapMin<T>`: `-elementos: ElementoHeap<T>*`, `-cantidad: int`, `-capacidad: int`. ctor con los 3, `~HeapMin()`. Métodos: `insertar`, `extraerMinimo`, `verMinimo`, `estaVacio`, `obtenerCantidad`, `subirElemento`, `bajarElemento`, `agrandarArreglo`.

### Estructuras/TablaHash/
- **NodoHash.h** `NodoHash<V>`: `-clave: std::string`, `-dato: V`, `-siguiente: NodoHash<V>*`. ctor con los 3. Métodos: `getClave`, `getDato`, `getSiguiente`, `setSiguiente`.
- **TablaHash.h** `TablaHash<V>`: `-tabla: NodoHash<V>**`, `-capacidad: int`, `-cantidad: int`, `-colisiones: int`. ctor con los 4, `~TablaHash()`. Métodos: `insertar`, `buscar`, `eliminar`, `obtenerTodos`, `obtenerCantidad`, `obtenerColisiones`, `calcularFactorDeCarga`, `funcionHash`.

### Estructuras/Redistribuidor/
- **Redistribuidor.h** `Redistribuidor` (no-template): `-codigos: std::string*`, `-faltantes: int*`, `-cantidadEstaciones: int`, `-capacidadCamion: int`, `-elegidas: bool*`, `-cantidadSoluciones: int`. ctor con los 6, `~Redistribuidor()`. Métodos: `buscarSoluciones`, `probar`, `mostrarSolucion`.

### Dominio/
- **Estacion.h** `Estacion`: `-codigo`, `-nombre`, `-barrio: std::string`, `-capacidadAnclajes: int`, `-bicisDisponibles: int`, `-colaEspera: Cola<int>`. ctor con los 6. Métodos: `getCodigo`, `calcularPorcentajeOcupacion`, `retirarBicicleta`, `devolverBicicleta`, `mostrarInformacion`.
- **Bicicleta.h** `Bicicleta`: `-id: int`, `-codigoEstacion`, `-tipo`, `-estado: std::string`, `-kilometros: int`. ctor con los 5. Métodos: `getId`, `getKilometros`, `estaAveriada`, `esElectrica`, `mostrarInformacion`.
- **Viaje.h** `Viaje`: `-id: int`, `-idBici: int`, `-dniUsuario: int`, `-estacionOrigen`, `-estacionDestino: std::string`, `-fecha: int`, `-duracionMin: int`. ctor con los 7. Métodos: `getFecha`, `getDniUsuario`, `getEstacionOrigen`, `getDuracionMin`, `mostrarInformacion`.

### Sistema/
- **SistemaBicis.h** `SistemaBicis`: `-estaciones: TablaHash<Estacion*>`, `-viajes: Lista<Viaje*>`, `-ciclovias: Grafo<std::string>`, `-bicicletas: ABB<int,Bicicleta*>`, `-taller: HeapMin<Bicicleta*>`. ctor con los 5, `~SistemaBicis()`. Métodos: `cargarDatosDesdeArchivos`, `buscarEstacionPorCodigo`, `agregarEstacion`, `eliminarEstacion`, `listarEstacionesOrdenadas`, `listarEstacionesConBajaOcupacion`, `mostrarRecorridoMasCorto`, `mostrarEstadisticasDelHash`, `contarViajesDesdeEstacionEnRango`, `mostrarViajesYMinutosDeUsuario`, `agregarBicicleta(int id, string codigoEstacion, string tipo, string estado, int kilometros)`, `buscarBicicletaPorId`, `listarBicicletasOrdenadasPorId`, `contarBicicletasAveriadas`, `listarBicicletasConMasKm`, `mostrarAlturaDelArbol`, `retirarBicicleta`, `devolverBicicleta`, `enviarBicicletaAlTaller`, `repararSiguienteBicicleta`, `planificarRedistribucion`.
- **Menu.h** `Menu`: `-sistema: SistemaBicis*`. ctor `(SistemaBicis* sistema)`. Métodos: `iniciarMenu`, `mostrarOpcionesDelMenu`, `procesarOpcionElegida`.

### Archivos/
- `.gitkeep` vacío.

## Compilación

`g++ -std=c++17 -Wall -Wextra main.cpp -o tp`
