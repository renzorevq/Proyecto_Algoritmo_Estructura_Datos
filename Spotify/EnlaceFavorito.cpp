#include "EnlaceFavorito.h"
#include <iostream>

bool EnlaceFavorito::agregarEnlace(const std::string& titulo, const std::string& url) {
    if (conteo >= MAX_ENLACES) return false;
    titulos[conteo] = titulo;
    enlaces[conteo] = url;
    conteo++;
    return true;
}

void EnlaceFavorito::listarFavoritos() const {
    std::cout << "=== Enlaces Favoritos ===\n";
    for (int i = 0; i < conteo; ++i) {
        std::cout << i + 1 << ". " << titulos[i] << ": " << enlaces[i] << "\n";
    }
    if (conteo == 0)
        std::cout << "(sin enlaces aún)\n";
    std::cout << "=========================\n";
}

bool EnlaceFavorito::eliminarEnlace(int indice) {
    if (indice < 0 || indice >= conteo) return false;
    for (int i = indice; i < conteo - 1; ++i) {
        titulos[i] = titulos[i + 1];
        enlaces[i] = enlaces[i + 1];
    }
    conteo--;
    return true;
}
