// ListaReproduccion.h

#pragma once

#include <string>
#include "ListaEnlazada.h"
#include "Cancion.h"

class ListaReproduccion {
private:
    std::string nombre;
    std::string descripcion;
    ListaEnlazada<Cancion> canciones;

public:
    ListaReproduccion();
    ListaReproduccion(const std::string& nombreLista,
        const std::string& descripcionLista);

    void agregarCancion(const Cancion& cancion);
    void eliminarCancion(const std::string& tituloCancion);
    void listarCanciones() const;
    std::string obtenerNombre() const;
    const ListaEnlazada<Cancion>& obtenerCanciones() const;
};
