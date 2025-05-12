// EstadisticaPista.h
#pragma once
#include "AdministradorEstadisticaPista.h"
#include <string>
#include <chrono>
#include <thread>

class EstadisticaPista : public AdministradorEstadisticaPista {
public:
    void registrarReproduccion(const std::string& titulo);
    void mostrarEstadisticas() const;
};
