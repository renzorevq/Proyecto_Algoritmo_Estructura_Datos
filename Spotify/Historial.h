#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAX_EVENTOS = 200;

class Historial {
private:
    string eventos[MAX_EVENTOS];
    int numEventos;

public:
    Historial();  

    void registrarEvento(const string& evento);
    void mostrarHistorial() const;
    bool estaVacio() const;
};
