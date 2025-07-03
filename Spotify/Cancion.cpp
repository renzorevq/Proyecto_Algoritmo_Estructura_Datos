#include "Cancion.h"
using namespace std;
// — Implementación de Cancion —
Cancion::Cancion() : titulo(""), artista(""), album(""), duracion(0) {}
Cancion::Cancion(const string& t, const string& a, const string& al, int d)
    : titulo(t), artista(a), album(al), duracion(d) {
}
string Cancion::obtenerTitulo() const { return titulo; }
string Cancion::obtenerArtista() const { return artista; }
string Cancion::obtenerAlbum() const { return album; }
int    Cancion::obtenerDuracion() const { return duracion; }