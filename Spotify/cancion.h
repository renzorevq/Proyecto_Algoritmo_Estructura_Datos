#pragma once
#include "Nodo.h"
#include "ListaEnlazada.h"
#include "Utilidades.h"
// using namespace std; // Ya declarado
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