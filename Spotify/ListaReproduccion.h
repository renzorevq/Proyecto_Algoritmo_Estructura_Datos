#pragma once
#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H

#include <string>
#include "ListaEnlazada.h"
#include "Cancion.h"

using namespace std;

class ListaReproduccion {
    string nombre;
    string descripcion;
    ListaEnlazada<Cancion> canciones;
public:
    ListaReproduccion();
    ListaReproduccion(const string& nombreListaReproduccion, const string& descripcionListaReproduccion);
    
    void agregarCancion(const Cancion& cancion);

    void eliminarCancion(const string& tituloCancion);
    
    void listarCanciones() const;
  
    string obtenerNombre() const;
};

#endif