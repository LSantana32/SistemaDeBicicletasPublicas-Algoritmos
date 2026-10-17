# Sistema de Bicicletas Públicas

## Descripción general

Sistema desarrollado en **C++ con orientación a objetos** para gestionar una red de estaciones de bicicletas públicas de la Ciudad de Buenos Aires.

El sistema permite administrar estaciones, bicicletas, viajes de usuarios y la redistribución de bicicletas entre estaciones mediante ciclovías.

Se utilizan estructuras de datos implementadas manualmente, junto con memoria dinámica y los conceptos vistos durante la cursada.

## Tecnologías y restricciones

- **Lenguaje:** C++17.
- **Paradigma:** Programación orientada a objetos.
- **Estructuras de datos:** Tabla hash, cola, heap, árbol binario de búsqueda y grafo.
- **Memoria dinámica:** Administración y liberación de memoria.
- **Restricción STL:** No se permite utilizar `vector`, `map`, `unordered_map`, `queue`, `priority_queue` ni `set`.
- Se permite utilizar `std::string` y la STL para lectura de archivos y tareas auxiliares.

## Archivos de entrada

El sistema utiliza archivos de texto con un registro por línea y campos separados por espacios.

### `estaciones.txt`

Contiene información de las estaciones.

| Campo | Descripción |
|---|---|
| `codigo` | Código identificador de la estación |
| `nombre` | Nombre de la estación |
| `barrio` | Barrio donde se encuentra |
| `capacidad_anclajes` | Capacidad máxima de bicicletas |
| `bicis_disponibles` | Cantidad de bicicletas disponibles |

Ejemplo:

```text
PLZ PlazaDeMayo Monserrat 30 12
PAL ParqueTresDeFebrero Palermo 40 35
CAB PrimeraJunta Caballito 25 4
```

### `bicicletas.txt`

Contiene información de las bicicletas.

| Campo | Descripción |
|---|---|
| `bici_id` | Identificador de la bicicleta |
| `codigo_estacion` | Código de la estación |
| `tipo` | `Mecanica` o `Electrica` |
| `estado` | `OK` o `Averiada` |
| `kilometros` | Kilómetros acumulados |

Ejemplo:

```text
501 PLZ Mecanica OK 1240
502 PAL Electrica Averiada 3810
```

### `viajes.txt`

Contiene el registro de los viajes realizados.

| Campo | Descripción |
|---|---|
| `viaje_id` | Identificador del viaje |
| `bici_id` | Identificador de la bicicleta utilizada |
| `dni_usuario` | DNI del usuario |
| `estacion_origen` | Código de la estación de origen |
| `estacion_destino` | Código de la estación de destino |
| `fecha` | Fecha del viaje en formato `AAAAMMDD` |
| `duracion_min` | Duración del viaje en minutos |

Ejemplo:

```text
9001 501 30123456 PLZ PAL 20260310 25
9002 502 27654321 PAL CAB 20260311 40
```

### `ciclovias.txt`

Indica qué estaciones están conectadas directamente mediante ciclovías. Las conexiones son bidireccionales.

Ejemplo:

```text
PLZ CAB
CAB PAL
```

## Funcionalidades

### A. Gestión de estaciones

- Consultar la información de una estación mediante su código.
- Agregar estaciones nuevas.
- Eliminar estaciones existentes, sin necesidad de reubicar sus bicicletas.
- Listar las estaciones ordenadas por capacidad de anclajes o cantidad de bicicletas disponibles.
- Listar las estaciones con menos del 20 % de ocupación.
- Calcular el recorrido con menor cantidad de tramos entre dos estaciones mediante búsqueda en anchura (BFS).
- Informar cuando no exista un recorrido entre dos estaciones.

**Estructuras de datos:**

- Tabla hash con resolución de colisiones para indexar las estaciones por código.
- Grafo para representar las conexiones entre estaciones.

El algoritmo de ordenamiento debe implementarse manualmente utilizando burbujeo, selección o inserción.

**Análisis requerido:**
- Cantidad de colisiones de la tabla hash con los datos de prueba.
- Factor de carga final de la tabla hash.

### B. Viajes y colas de espera

- Calcular la cantidad de viajes que salieron de una estación dentro de un rango de fechas.
- Buscar todos los viajes de un usuario por su DNI y calcular el total de minutos pedaleados.
- Listar las bicicletas que superen una cantidad de kilómetros indicada por el usuario.
- Implementar una cola de espera por estación para asignar bicicletas a los usuarios en orden de llegada.
- Implementar una cola de prioridad mediante un min-heap para gestionar las bicicletas averiadas que ingresan al taller.

**Análisis de complejidad temporal y estructuras de datos**

**1. Cantidad de viajes por estación y rango de fechas**

**Complejidad temporal:** \(O(n)\)

Se eligió una lista enlazada para almacenar los viajes porque permite recorrerlos secuencialmente sin modificar la estructura existente del sistema. Como no existe un índice que permita acceder directamente a los viajes de un usuario por su DNI, es necesario recorrer la lista completa para encontrar todos los viajes correspondientes y sumar sus duraciones. Por este motivo, la complejidad temporal es \(O(n)\), donde \(n\) representa la cantidad total de viajes almacenados.

**2. Viajes de un usuario por DNI y total de minutos pedaleados**

**Complejidad temporal:** \(O(n)\)

Se reutilizó la lista enlazada de viajes existente, ya que permite examinar cada registro y comprobar si cumple con las condiciones de estación de origen y rango de fechas. Como no se dispone de un índice organizado por estación y fecha, en el peor caso es necesario recorrer todos los viajes para obtener la cantidad solicitada. Por lo tanto, la complejidad temporal es \(O(n)\), donde \(n\) es la cantidad total de viajes almacenados.

**Prioridades del taller:**

- Prioridad 1: máxima urgencia.
- Prioridad 2: urgencia intermedia.
- Prioridad 3: menor urgencia.
- Las bicicletas eléctricas averiadas ingresan siempre con prioridad 1.

La cola de prioridad debe permitir insertar una bicicleta y extraer la más urgente.

**Análisis requerido:**

Para cada punto, indicar la complejidad temporal en notación Big O y explicar en dos o tres oraciones por qué se eligió esa estructura de datos.

### C. Registro de bicicletas con árbol binario de búsqueda

Todas las bicicletas de la red se almacenan en un árbol binario de búsqueda (ABB), ordenado por `bici_id`.

Funcionalidades:

- Insertar una bicicleta en el árbol.
- Buscar una bicicleta por su ID y mostrar sus datos.
- Listar todas las bicicletas ordenadas por ID mediante un recorrido *inorder*.
- Contar las bicicletas averiadas recorriendo el árbol.
- Calcular la altura del árbol.
- Liberar toda la memoria del árbol al finalizar el programa mediante un recorrido *postorder*.

**Análisis requerido:**

Explicar qué altura tendría el árbol si las bicicletas se cargaran ordenadas por ID y cómo afectaría esto al costo de búsqueda. Incluir un ejemplo con cinco bicicletas.

**Funcionalidad opcional:**

Eliminar bicicletas del árbol contemplando los tres casos:

- Nodo hoja.
- Nodo con un hijo.
- Nodo con dos hijos.

### D. Redistribución con backtracking

Un camión recorre la ciudad para llevar bicicletas a las estaciones que necesitan unidades adicionales. Tiene capacidad para transportar exactamente `C` bicicletas y debe descargar la carga completa.

**Entrada:**
- Capacidad `C` del camión.
- Lista de estaciones y cantidad de bicicletas que le faltan a cada una.

**Salida:**
- Todos los subconjuntos de estaciones cuyos faltantes sumen exactamente `C`.
- Informar si no existe ninguna combinación válida.

**Requisitos:**
- Implementar la solución mediante *backtracking*.
- Indicar la complejidad temporal en el peor caso.

**Ejemplo:**

Con `C = 10` y los siguientes faltantes:

| Estación | Bicicletas faltantes |
|---|---:|
| PLZ | 3 |
| CAB | 7 |
| RET | 5 |
| CON | 2 |
| BOE | 5 |

Las soluciones son:

- `{PLZ, CAB}`
- `{RET, BOE}`
- `{PLZ, RET, CON}`
- `{PLZ, CON, BOE}`

## Condiciones de entrega

- Exposición de avances cada dos semanas, con el código funcionando.
- Entrega final con defensa oral del proyecto.
- Diagrama de clases UML con las relaciones de asociación y composición.
- Menú por consola que permita probar todas las funcionalidades.
- Variables y métodos en `camelCase`.
- Clases en `PascalCase`.
- Clases originales y de elaboración propia.

## Compilación

El programa debe compilar sin advertencias utilizando `g++` con C++17 y las opciones `
