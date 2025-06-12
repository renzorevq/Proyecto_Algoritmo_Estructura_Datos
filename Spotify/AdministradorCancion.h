#pragma once
#ifndef ADMINISTRADORDECANCION_H
#define ADMINISTRADORDECANCION_H

#include "Cancion.h"
#include <iostream>
#include <string>
using namespace std;
const int MAX_CANCIONES = 100;

class AdministradorDeCancion {
private:
    Cancion canciones[MAX_CANCIONES];     
    int cantidad = 0;

public:
    AdministradorDeCancion() = default;

    bool agregarCancion(const Cancion& cancion);
    bool eliminarCancion(const string& titulo);
    void listarCanciones() const;
    int obtenerCantidad() const;
    Cancion* buscarCancion(const string& titulo);
};

#endif
