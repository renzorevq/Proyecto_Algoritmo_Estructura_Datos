// DatosValoracion.h
#pragma once

#include "AdministradorDatosValoracion.h"
#include <string>

class DatosValoracion : public AdministradorDatosValoracion {
public:
    // Agrega una valoraci�n del 1 al 5
    bool agregarValoracion(const std::string& titulo, int valor);

    // Muestra las valoraciones promedio
    void listarPromedios() const;

    // Devuelve el promedio de una canci�n espec�fica
    float obtenerPromedio(const std::string& titulo) const;

    int obtenerCantidad() const { return conteo; }
};
