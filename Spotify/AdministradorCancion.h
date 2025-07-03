#pragma once
#include "Cancion.h"
static const int MAX_CANCIONES = 100;
class AdministradorCancion {
private:
    Cancion canciones[MAX_CANCIONES];
    int cantidad = 0;
public:
    AdministradorCancion() = default;
    bool agregarCancion(const Cancion& cancion);
    bool eliminarCancion(const string& titulo);
    void listarCanciones() const;
    int obtenerCantidad() const;
    Cancion* buscarCancion(const string& titulo);
};