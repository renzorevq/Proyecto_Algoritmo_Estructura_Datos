#pragma once
#include <string>
#include <vector>

class Historial {
private:
    std::vector<std::string> eventos;

public:
    void registrarEvento(const std::string& evento);
    void mostrarHistorial() const;
    bool estaVacio() const;
};
