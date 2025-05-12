
#pragma once
#include <string>

class AdministradorEstadisticaPista {
protected:
    static const int MAX_CANCIONES = 100;
    std::string titulos[MAX_CANCIONES];
    int conteos[MAX_CANCIONES]{};
    int cantidad = 0;
};
