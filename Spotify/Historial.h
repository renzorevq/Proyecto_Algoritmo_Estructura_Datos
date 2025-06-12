#pragma once
#include <string>
#include <vector>
using namespace std;
class Historial {
private:
    vector<string> eventos;

public:
    void registrarEvento(const string& evento);
    void mostrarHistorial() const;
    bool estaVacio() const;
};
