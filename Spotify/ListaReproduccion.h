#pragma once
#include <string>
#include "ListaEnlazada.h"
#include "Cancion.h"
using namespace std;
class ListaReproduccion {
private:
    string nombre;
    string descripcion;
    ListaEnlazada<Cancion> canciones;
public:
    ListaReproduccion();
    ListaReproduccion(const string& nombreLista,
        const string& descripcionLista);
    void agregarCancion(const Cancion& cancion);
    void eliminarCancion(const string& tituloCancion);
    void listarCanciones() const;
    string obtenerNombre() const;
    ListaEnlazada<Cancion>& obtenerCanciones();
};