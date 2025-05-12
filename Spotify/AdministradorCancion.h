#pragma once
#ifndef ADMINISTRADORDECANCION_H
#define ADMINISTRADORDECANCION_H

#include "Cancion.h"
#include <iostream>
#include <string>

const int MAX_CANCIONES = 100;

class AdministradorDeCancion {
private:
    Cancion canciones[MAX_CANCIONES];     
    int cantidad = 0;

public:
    AdministradorDeCancion() = default;

    bool agregarCancion(const Cancion& cancion);
    bool eliminarCancion(const std::string& titulo);
    void listarCanciones() const;
    int obtenerCantidad() const;
    Cancion* buscarCancion(const std::string& titulo);
};

#endif
