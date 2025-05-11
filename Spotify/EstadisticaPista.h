#pragma once
#include <string>
#include <chrono>
#include <thread>

class EstadisticaPista {
    static const int MAX_CANCIONES = 100;
    std::string titulos[MAX_CANCIONES];
    int conteos[MAX_CANCIONES];
    int cantidad = 0;

public:
    void registrarReproduccion(const std::string& titulo);
    void mostrarEstadisticas() const;
};
