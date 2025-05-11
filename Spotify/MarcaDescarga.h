#pragma once
#include <string>
#include <iostream>

class MarcaDescarga {
private:
    static const int MAX = 100;
    std::string titulos[MAX];
    int conteoDescargas[MAX];
    int cantidad = 0;

public:
    bool registrarDescarga(const std::string& titulo);
    void mostrarDescargas() const;
};
