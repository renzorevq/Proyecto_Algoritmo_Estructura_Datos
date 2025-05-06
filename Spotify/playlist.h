#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "./listaEnlazada.h"
#include "./cancion.h"

using namespace std;

class Playlist {
    string nombre;
    string descripcion;
    ListaEnlazada<Cancion> canciones;
public:
    Playlist() {}
    Playlist(const string& nombrePlaylist, const string& descripcionPlaylist);
    
    void agregarCancion(const Cancion& cancion);

    void eliminarCancion(const string& tituloCancion);
    
    void listarCanciones() const;
  
    string obtenerNombre() const;
};

#endif