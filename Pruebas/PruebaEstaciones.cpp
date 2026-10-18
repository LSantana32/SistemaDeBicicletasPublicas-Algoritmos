// Prueba de agregar y eliminar estaciones en SistemaBicis.
// Compilar desde la carpeta del proyecto:
#include <iostream>
#include <string>
#include "../Sistema/SistemaBicis.h"

int fallas = 0;

void verificar(bool condicion, std::string descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << "\n";
    } else {
        std::cout << "[FALLA] " << descripcion << "\n";
        fallas++;
    }
}

int main() {
    SistemaBicis sistema;

    // Agregar (el sistema se hace cargo de cada estacion que recibe)
    sistema.agregarEstacion(new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12));
    sistema.agregarEstacion(new Estacion("PAL", "ParqueTresDeFebrero", "Palermo", 40, 35));
    sistema.agregarEstacion(new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4));
    sistema.agregarEstacion(new Estacion("PLZ", "Repetida", "Otro", 10, 5));   // repetida: se rechaza y se libera
    sistema.agregarEstacion(new Estacion("AB", "Corta", "Barrio", 10, 5));     // codigo invalido: idem

    // Si se agregaron bien, se pueden eliminar una vez
    verificar(sistema.eliminarEstacion("PAL"), "PAL se habia agregado y se puede eliminar");
    verificar(!sistema.eliminarEstacion("PAL"), "no se puede eliminar dos veces");
    verificar(!sistema.eliminarEstacion("AB"), "la de codigo invalido no se agrego");
    verificar(!sistema.eliminarEstacion("RET"), "no elimina una estacion que no existe");
    verificar(sistema.eliminarEstacion("PLZ"), "PLZ esta una sola vez (la repetida no entro)");
    verificar(!sistema.eliminarEstacion("PLZ"), "despues de eliminarla PLZ ya no esta");

    std::cout << "\n";
    sistema.mostrarEstadisticasDelHash();   // tiene que quedar 1 estacion (CAB)

    // CAB queda adentro: el destructor de SistemaBicis tiene que liberarla
    std::cout << (fallas == 0 ? "\nTodo OK\n" : "\nHay pruebas que fallan\n");
    return fallas == 0 ? 0 : 1;
}