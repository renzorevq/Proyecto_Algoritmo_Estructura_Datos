#include "Historial.h"
Historial::Historial() : numEventos(0) {}
void Historial::registrarEvento(const string& evento) {
    if (numEventos < MAX_EVENTOS) {
        eventos[numEventos++] = evento;
    }
}
void Historial::mostrarHistorial() const {
    if (numEventos == 0) {
        cout << "(No hay eventos registrados)\n";
        return;
    }
    cout << "=== HISTORIAL DE ACTIVIDADES ===\n";
    for (int i = 0; i < numEventos; ++i) {
        cout << "- " << eventos[i] << "\n";
    }
    cout << "================================\n";
}
bool Historial::estaVacio() const {
    return numEventos == 0;
}