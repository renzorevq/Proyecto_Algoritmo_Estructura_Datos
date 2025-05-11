#pragma once
#include <string>

class EnlaceFavorito {
    static const int MAX_ENLACES = 100;
    std::string titulos[MAX_ENLACES];
    std::string enlaces[MAX_ENLACES];
    int conteo = 0;

public:
    bool agregarEnlace(const std::string& titulo, const std::string& url);
    void listarFavoritos() const;
    bool eliminarEnlace(int indice);
    int obtenerCantidad() const { return conteo; }
};
