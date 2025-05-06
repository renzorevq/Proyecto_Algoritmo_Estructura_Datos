#include <string>
#include "cancion.h"

using namespace std;

Cancion::Cancion() {};
Cancion::Cancion(const string& tituloCancion,
    const string& nombreArtista,
    const string& nombreAlbum,
    int duracionSegundos) : titulo(tituloCancion), artista(nombreArtista), album(nombreAlbum), duracion(duracionSegundos) {
}

string Cancion::obtenerTitulo() const { return titulo; }
string Cancion::obtenerArtista() const { return artista; }
