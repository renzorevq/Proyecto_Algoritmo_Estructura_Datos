#pragma once
#include <string>
#include "AdministradorEnlaceFavorito.h"
using namespace std;
class EnlaceFavorito : public AdministradorEnlaceFavorito {
public:
    bool agregarEnlace(const string& titulo, const string& url);
    void listarFavoritos() const;
    bool eliminarEnlace(int indice);
    int obtenerCantidad() const { return conteo; }
};
