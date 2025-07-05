#include "Historial.h"

Historial::Historial() : numEventos(0) {}

void Historial::registrarEvento(const string& evento) {
    if (numEventos < MAX_EVENTOS) {
        eventos[numEventos++] = evento;
    }
}

void Historial::mostrarHistorial() const {
    if (numEventos == 0) {
        cout << "-> No hay actividades registradas.\n";
        return;
    }

    cout << "\n-- REGISTRO DE ACTIVIDADES --\n\n";
    for (int i = 0; i < numEventos; ++i) {
        cout << i + 1 << ". " << eventos[i] << "\n";
    }

    cout << "\n-> Total de eventos registrados: " << numEventos << "\n";
}

bool Historial::estaVacio() const {
    return numEventos == 0;
}
