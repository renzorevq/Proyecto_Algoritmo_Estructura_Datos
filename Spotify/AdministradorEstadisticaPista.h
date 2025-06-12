
#pragma once
#include <string>
using namespace std;
class AdministradorEstadisticaPista {
protected:
    static const int MAX_CANCIONES = 100;
    string titulos[MAX_CANCIONES];
    int conteos[MAX_CANCIONES]{};
    int cantidad = 0;
};
