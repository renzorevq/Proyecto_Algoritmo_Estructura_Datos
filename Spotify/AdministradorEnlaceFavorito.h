#pragma once
#include <string>

class AdministradorEnlaceFavorito {
protected:
    static const int MAX_ENLACES = 100;
    std::string titulos[MAX_ENLACES];
    std::string enlaces[MAX_ENLACES];
    int conteo = 0;
};