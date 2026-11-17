#pragma once

#include <limits>

#include "SistemaBicis.h"

class Menu {
    private:
        SistemaBicis* sistema;

        int leerEntero(std::string mensaje) {
            int valor = 0;
            std::cout << mensaje;

            while (!(std::cin >> valor)) {
                if (std::cin.eof()) {
                    return 0;
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada invalida.\n" << mensaje;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }

        std::string leerLinea(std::string mensaje) {
            std::string valor;
            std::cout << mensaje;
            std::getline(std::cin, valor);
            return valor;
        }

        std::string leerCodigo(std::string mensaje) {
            std::string valor = leerLinea(mensaje);

            while (valor.length() != 3) {
                if (std::cin.eof()) {
                    return valor;
                }

                std::cout << "Codigo invalido. Debe tener exactamente 3 caracteres.\n";
                valor = leerLinea(mensaje);
            }

            return valor;
        }

        int leerEnteroPositivo(std::string mensaje) {
            int valor = leerEntero(mensaje);

            while (valor <= 0) {
                if (std::cin.eof()) {
                    return valor;
                }

                std::cout << "Valor invalido. Debe ser mayor que 0.\n";
                valor = leerEntero(mensaje);
            }

            return valor;
        }

        int leerEnteroNoNegativo(std::string mensaje) {
            int valor = leerEntero(mensaje);

            while (valor < 0) {
                if (std::cin.eof()) {
                    return valor;
                }

                std::cout << "Valor invalido. No puede ser negativo.\n";
                valor = leerEntero(mensaje);
            }

            return valor;
        }

        int leerEnteroEnRango(std::string mensaje, int minimo, int maximo) {
            int valor = leerEntero(mensaje);

            while (valor < minimo || valor > maximo) {
                if (std::cin.eof()) {
                    return valor;
                }

                std::cout << "Valor invalido. Debe estar entre " << minimo
                        << " y " << maximo << ".\n";
                valor = leerEntero(mensaje);
            }

            return valor;
        }

    public:
        Menu(SistemaBicis* sistema) {
            this->sistema = sistema;
        }

        void iniciarMenu() {
            int opcion = -1;

            do {
                mostrarOpcionesDelMenu();
                opcion = leerEntero("Opcion: ");
                procesarOpcionElegida(opcion);

                if (opcion != 0) {
                    std::cout << "\nPresione Enter para continuar...";
                    std::cin.get();
                }
            } while (opcion != 0);
        }

        void mostrarOpcionesDelMenu() {
            std::cout << "\n===== SISTEMA DE BICICLETAS PUBLICAS =====\n";
            std::cout << "--- Estaciones ---\n";
            std::cout << " 1. Consultar estacion por codigo\n";
            std::cout << " 2. Agregar estacion\n";
            std::cout << " 3. Eliminar estacion\n";
            std::cout << " 4. Listar estaciones por capacidad de anclajes\n";
            std::cout << " 5. Listar estaciones por bicicletas disponibles\n";
            std::cout << " 6. Listar estaciones con baja ocupacion\n";
            std::cout << " 7. Recorrido mas corto entre dos estaciones\n";
            std::cout << " 8. Estadisticas de la tabla hash\n";
            std::cout << "--- Viajes ---\n";
            std::cout << " 9. Contar viajes desde una estacion en un rango de fechas\n";
            std::cout << "10. Viajes y minutos pedaleados de un usuario\n";
            std::cout << "--- Bicicletas ---\n";
            std::cout << "11. Agregar bicicleta\n";
            std::cout << "12. Buscar bicicleta por ID\n";
            std::cout << "13. Listar bicicletas ordenadas por ID\n";
            std::cout << "14. Contar bicicletas averiadas\n";
            std::cout << "15. Listar bicicletas con mas de X kilometros\n";
            std::cout << "16. Mostrar altura del arbol de bicicletas\n";
            std::cout << "--- Operaciones ---\n";
            std::cout << "17. Retirar bicicleta de una estacion\n";
            std::cout << "18. Devolver bicicleta en una estacion\n";
            std::cout << "19. Enviar bicicleta al taller\n";
            std::cout << "20. Reparar la siguiente bicicleta del taller\n";
            std::cout << "21. Planificar redistribucion con el camion\n";
            std::cout << "22. Eliminar bicicleta del arbol\n";
            std::cout << " 0. Salir\n";
        }

        void procesarOpcionElegida(int opcion) {
            switch (opcion) {
                case 1: {
                    std::string codigo = leerCodigo("Codigo de la estacion: ");
                    sistema->mostrarInformacionDeEstacionPorCodigo(codigo);
                    break;
                }

                case 2: {
                    std::string codigo = leerCodigo("Codigo (3 caracteres): ");
                    std::string nombre = leerLinea("Nombre: ");
                    std::string barrio = leerLinea("Barrio: ");
                    int capacidad = leerEnteroPositivo("Capacidad de anclajes: ");
                    int disponibles = leerEnteroEnRango(
                        "Bicicletas disponibles: ", 0, capacidad);

                    if (disponibles > 0) {
                        std::cout << "La estacion se crea sin bicicletas registradas. "
                                    "Agreguelas con la opcion 11.\n";
                        disponibles = 0;
                    }

                    sistema->agregarEstacion(
                        new Estacion(codigo, nombre, barrio, capacidad, disponibles));
                    break;
                }

                case 3: {
                    std::string codigo = leerCodigo("Codigo de la estacion a eliminar: ");
                    if (sistema->eliminarEstacion(codigo)) {
                        std::cout << "Estacion " << codigo << " eliminada.\n";
                    } else {
                        std::cout << "No existe una estacion con codigo "
                                << codigo << ".\n";
                    }
                    break;
                }

                case 4:
                    sistema->listarEstacionesOrdenadas(1);
                    break;

                case 5:
                    sistema->listarEstacionesOrdenadas(2);
                    break;

                case 6:
                    sistema->listarEstacionesConBajaOcupacion();
                    break;

                case 7: {
                    std::string origen = leerCodigo("Estacion de origen: ");
                    std::string destino = leerCodigo("Estacion de destino: ");
                    sistema->mostrarRecorridoMasCorto(origen, destino);
                    break;
                }

                case 8:
                    sistema->mostrarEstadisticasDelHash();
                    break;

                case 9: {
                    std::string codigo = leerCodigo("Codigo de la estacion de origen: ");
                    int desde = leerEntero("Fecha desde (AAAAMMDD): ");
                    int hasta = leerEntero("Fecha hasta (AAAAMMDD): ");
                    int cantidad = 0;

                    if (sistema->contarViajesDesdeEstacionEnRango(
                            codigo, desde, hasta, cantidad)) {
                        std::cout << "Cantidad de viajes: " << cantidad << '\n';
                    }
                    break;
                }

                case 10: {
                    int dni = leerEntero("DNI del usuario: ");
                    sistema->mostrarViajesYMinutosDeUsuario(dni);
                    break;
                }

                case 11: {
                    int id = leerEntero("ID de la bicicleta: ");
                    std::string codigoEstacion = leerCodigo("Codigo de la estacion: ");
                    std::string tipo = leerLinea("Tipo: ");
                    std::string estado = leerLinea("Estado: ");
                    int kilometros = leerEntero("Kilometros: ");
                    sistema->agregarBicicleta(
                        id, codigoEstacion, tipo, estado, kilometros);
                    break;
                }

                case 12: {
                    int id = leerEntero("ID de la bicicleta: ");
                    Bicicleta* bicicleta = sistema->buscarBicicletaPorId(id);
                    if (bicicleta != nullptr) {
                        bicicleta->mostrarInformacion();
                    } else {
                        std::cout << "No se encontro una bicicleta con ID "
                                << id << ".\n";
                    }
                    break;
                }

                case 13:
                    sistema->listarBicicletasOrdenadasPorId();
                    break;

                case 14:
                    std::cout << "Bicicletas averiadas: "
                            << sistema->contarBicicletasAveriadas() << '\n';
                    break;

                case 15: {
                    int kmMinimo = leerEntero("Kilometros minimos: ");
                    sistema->listarBicicletasConMasKm(kmMinimo);
                    break;
                }

                case 16:
                    sistema->mostrarAlturaDelArbol();
                    break;

                case 17: {
                    std::string codigo = leerCodigo("Codigo de la estacion: ");
                    int dni = leerEntero("DNI del usuario: ");
                    int fechaActual = leerEntero("Fecha actual (AAAAMMDD): ");
                    sistema->retirarBicicleta(codigo, dni, fechaActual);
                    break;
                }

                case 18: {
                    std::string codigo = leerCodigo("Codigo de la estacion: ");
                    int dni = leerEntero("DNI del usuario: ");
                    int duracion = leerEnteroNoNegativo("Duracion del viaje (minutos): ");
                    int kilometros = leerEnteroNoNegativo("Kilometros recorridos: ");
                    sistema->devolverBicicleta(codigo, dni, duracion, kilometros);
                    break;
                }

                case 19: {
                    int id = leerEntero("ID de la bicicleta: ");
                    int prioridad = leerEntero("Prioridad (1 alta, 2 media, 3 baja): ");
                    sistema->enviarBicicletaAlTaller(id, prioridad);
                    break;
                }

                case 20:
                    sistema->repararSiguienteBicicleta();
                    break;

                case 21: {
                    int capacidad = leerEnteroPositivo("Capacidad del camion: ");
                    int cantidad = leerEnteroPositivo("Cantidad de estaciones: ");

                    if (capacidad <= 0 || cantidad <= 0) {
                        break;
                    }

                    std::string* codigos = new std::string[cantidad];
                    int* faltantes = new int[cantidad];

                    for (int i = 0; i < cantidad; i++) {
                        std::cout << "Estacion " << (i + 1) << ":\n";
                        codigos[i] = leerLinea("  Codigo: ");
                        faltantes[i] = leerEnteroPositivo("  Bicicletas faltantes: ");
                    }

                    sistema->planificarRedistribucion(
                        capacidad, codigos, faltantes, cantidad);

                    delete[] codigos;
                    delete[] faltantes;
                    break;
                }

                case 22: {
                    int id = leerEntero("ID de la bicicleta a eliminar: ");
                    if (sistema->eliminarBicicleta(id)) {
                        std::cout << "Bicicleta " << id << " eliminada.\n";
                    }
                    break;
                }

                case 0:
                    std::cout << "Saliendo del sistema...\n";
                    break;

                default:
                    std::cout << "Opcion invalida.\n";
                    break;
            }
        }
};
