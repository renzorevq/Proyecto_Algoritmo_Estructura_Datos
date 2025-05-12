
#pragma once
#include <string>

class AdministradorDatosValoracion {
protected:
    static const int MAX_VAL = 100;
    std::string titulos[MAX_VAL];
    int sumaValoracion[MAX_VAL]{};
    int cantidadValoraciones[MAX_VAL]{};
    int conteo = 0;
};
