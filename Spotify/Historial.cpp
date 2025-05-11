#include "Historial.h"
#include <iostream>

void Historial::registrarEvento(const std::string& evento) {
    eventos.push_back(evento);
}

void Historial::mostrarHistorial() const {
    if (eventos.empty()) {
        std::cout << "(No hay eventos registrados)\n";
    }
    else {
        std::cout << "=== HISTORIAL DE ACTIVIDADES ===\n";
        for (const auto& e : eventos) {
            std::cout << "- " << e << "\n";
        }
        std::cout << "================================\n";
    }
}

bool Historial::estaVacio() const {
    return eventos.empty();
}
