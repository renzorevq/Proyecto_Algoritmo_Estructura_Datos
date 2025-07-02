#include "AdministradorCompartirCancion.h"
#include <iostream>

AdministradorCompartirCancion::AdministradorCompartirCancion()
    : cantidadCompartidos(0), semilla(0) {
}

void AdministradorCompartirCancion::inicializarSemilla() const {
    if (semilla == 0) {
        semilla = static_cast<unsigned int>(time(nullptr));
        if (semilla == 0) semilla = 1;
    }
}

int AdministradorCompartirCancion::generarDigitoAleatorio() const {
    inicializarSemilla();
    semilla = semilla * 1103515245u + 12345u;
    return static_cast<int>((semilla / 65536u) % 10u);
}

string AdministradorCompartirCancion::generarCodigo() const {
    string codigo;
    for (int i = 0; i < 3; ++i) {
        codigo += char('0' + generarDigitoAleatorio());
    }
    return codigo;
}

bool AdministradorCompartirCancion::agregarCompartido(const string& titulo, const string& enlaceBase) {
    if (cantidadCompartidos >= MAX_COMPARTIDOS) return false;
    titulos[cantidadCompartidos] = titulo;
    enlaces[cantidadCompartidos] = enlaceBase + generarCodigo();
    ++cantidadCompartidos;
    return true;
}

int AdministradorCompartirCancion::obtenerCantidad() const {
    return cantidadCompartidos;
}

void AdministradorCompartirCancion::listarCompartidos() const {
    if (cantidadCompartidos == 0) {
        cout << "(No hay canciones compartidas aun)\n";
        return;
    }
    for (int i = 0; i < cantidadCompartidos; ++i) {
        cout << i + 1 << ". " << titulos[i]
            << " -> " << enlaces[i] << "\n";
    }
}
