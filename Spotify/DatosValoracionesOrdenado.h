#pragma once
#include "Cancion.h"
#include "listaEnlazada.h"
#include "AdministradorCancion.h"

class DatosValoracionesOrdenado{
public:
    // Ordena el arreglo de canciones según el título
    void ordenarporTitulo(Cancion canciones[], int cantidad);
};
