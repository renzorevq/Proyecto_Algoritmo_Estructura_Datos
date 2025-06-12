#pragma once
#include "AdministradorEstadisticaPista.h"
#include <string>
#include <chrono>
#include <thread>
using namespace std;
class EstadisticaPista : public AdministradorEstadisticaPista {
public:
    void registrarReproduccion(const string& titulo);
    void mostrarEstadisticas() const;
};
