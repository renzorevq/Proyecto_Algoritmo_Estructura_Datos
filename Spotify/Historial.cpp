#include "Historial.h"
#include <iostream>

void Historial::registrarEvento(const string& evento) {
    eventos.push_back(evento);
}

void Historial::mostrarHistorial() const {
    if (eventos.empty()) {
        cout << "(No hay eventos registrados)\n";
    }
    else {
        cout << "=== HISTORIAL DE ACTIVIDADES ===\n";
        for (const auto& e : eventos) {
            cout << "- " << e << "\n";
        }
        cout << "================================\n";
    }
}

bool Historial::estaVacio() const {
    return eventos.empty();
}
