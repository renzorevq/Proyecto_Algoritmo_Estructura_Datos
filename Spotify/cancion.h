#pragma once

#include <string>

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
    string obtenerAlbum()const;
    int obtenerDuracion() const;
};
