#include "Sistema/Menu.h"

int main() {
    SistemaBicis sistema;                 // crea el sistema vacío
    sistema.cargarDatosDesdeArchivos();   // carga los archivos de datos
    Menu menu(&sistema);                  // le pasa al menú la dirección del sistema
    menu.iniciarMenu();
    return 0;
}
