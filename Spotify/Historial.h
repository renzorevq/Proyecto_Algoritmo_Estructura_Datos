#pragma once

#include <string>
#include <iostream>
using namespace std;

static const int MAX_EVENTOS = 100;

class Historial {
private:
    string eventos[MAX_EVENTOS];
    int numEventos;

public:
    Historial();

    // Registra un evento, si hay espacio
    void registrarEvento(const string& evento);

    // Muestra todos los eventos guardados
    void mostrarHistorial() const;

    // Indica si está vacío
    bool estaVacio() const;
};
