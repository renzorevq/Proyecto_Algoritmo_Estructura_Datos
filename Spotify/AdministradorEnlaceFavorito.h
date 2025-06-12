#pragma once
#include <string>
using namespace std;
class AdministradorEnlaceFavorito {
protected:
    static const int MAX_ENLACES = 100;
    string titulos[MAX_ENLACES];
    string enlaces[MAX_ENLACES];
    int conteo = 0;
};