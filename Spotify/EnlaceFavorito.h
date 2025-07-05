#pragma once
#include "GeneradorEnlaceFavorito.h"

class EnlaceFavorito : public GeneradorEnlaceFavorito {
public:
    bool agregarEnlace(const string& titulo, const string& url);
    void listarFavoritos() const;
    bool eliminarEnlace(int indice);
    int obtenerCantidad() const { return conteo; }
};