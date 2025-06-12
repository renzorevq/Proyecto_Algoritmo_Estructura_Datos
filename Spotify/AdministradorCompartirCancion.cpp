#include "CompartirCancion.h"
#include "AdministradorCompartirCancion.h"
#include <iostream>
#include <cstdlib>

string AdministradorCompartirCancion::generarCodigo() const {
    string codigo;
    for (int i = 0; i < 3; ++i) {
        codigo += char('0' + (rand() % 10));
    }
    return codigo;
}

bool AdministradorCompartirCancion::agregarCompartido(const string& titulo, const string& link) {
    if (conteo >= MAX_COMPARTIDOS) return false;
    titulos[conteo] = titulo;
    links[conteo] = link + generarCodigo();
    ++conteo;
    return true;
}

int AdministradorCompartirCancion::obtenerCantidad() const {
    return conteo;
}

void AdministradorCompartirCancion::listarCompartidos() const {
    if (conteo == 0) {
        cout << "(No hay canciones compartidas aun)\n";
        return;
    }
    for (int i = 0; i < conteo; ++i) {
        std::cout << i + 1 << ". " << titulos[i]
            << " -> " << links[i] << "\n";
    }
}
