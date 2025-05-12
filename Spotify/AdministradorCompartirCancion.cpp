#include "CompartirCancion.h"
#include "AdministradorCompartirCancion.h"
#include <iostream>
#include <cstdlib>

std::string AdministradorCompartirCancion::generarCodigo() const {
    std::string codigo;
    for (int i = 0; i < 3; ++i) {
        codigo += char('0' + (std::rand() % 10));
    }
    return codigo;
}

bool AdministradorCompartirCancion::agregarCompartido(const std::string& titulo, const std::string& link) {
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
        std::cout << "(No hay canciones compartidas aún)\n";
        return;
    }
    for (int i = 0; i < conteo; ++i) {
        std::cout << i + 1 << ". " << titulos[i]
            << " -> " << links[i] << "\n";
    }
}
