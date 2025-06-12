#pragma once

#include <string>
#include "Nodo.h"
#include "ListaEnlazada.h"
#include "Utilidades.h"
using namespace std;

class Cancion {
private:
    string titulo;
    string artista;
    string album;
    int duracion;
public:
    Cancion();
    Cancion(const string& tituloCancion,
        const string& nombreArtista,
        const string& nombreAlbum,
        int duracionSegundos);

    string obtenerTitulo() const;
    string obtenerArtista() const;
    string obtenerAlbum()   const;
    int obtenerDuracion()   const;
};

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


    const ListaEnlazada<Cancion>& obtenerCanciones() const;
};
