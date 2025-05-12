#pragma once
#include <string>
#include "AdministradorEnlaceFavorito.h"

class EnlaceFavorito : public AdministradorEnlaceFavorito {
public:
    bool agregarEnlace(const std::string& titulo, const std::string& url);
    void listarFavoritos() const;
    bool eliminarEnlace(int indice);
    int obtenerCantidad() const { return conteo; }
};
