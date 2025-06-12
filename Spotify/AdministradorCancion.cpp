#include <string>
#include "Cancion.h"
#include "AdministradorCancion.h"


Cancion::Cancion() : titulo(""), artista(""), album(""), duracion(0) {}

Cancion::Cancion(const string& tituloCancion, const string& nombreArtista,
    const string& nombreAlbum, int duracionSegundos)
    : titulo(tituloCancion), artista(nombreArtista), album(nombreAlbum), duracion(duracionSegundos) {
}

string Cancion::obtenerTitulo() const { return titulo; }
string Cancion::obtenerArtista() const { return artista; }
string Cancion::obtenerAlbum() const { return album; }
int Cancion::obtenerDuracion() const { return duracion; }


bool AdministradorDeCancion::agregarCancion(const Cancion& cancion) {
    if (cantidad >= MAX_CANCIONES) {
        cout << "Error: No se puede agregar mas canciones. Limite alcanzado.\n";
        return false;
    }
    canciones[cantidad++] = cancion;
    return true;
}

bool AdministradorDeCancion::eliminarCancion(const string& titulo) {
    for (int i = 0; i < cantidad; ++i) {
        if (canciones[i].obtenerTitulo() == titulo) {
            for (int j = i; j < cantidad - 1; ++j)
                canciones[j] = canciones[j + 1];
            cantidad--;
            return true;
        }
    }
    return false;
}

void AdministradorDeCancion::listarCanciones() const {
    if (cantidad == 0) {
        cout << "No hay canciones registradas.\n";
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        cout << i + 1 << ". " << canciones[i].obtenerTitulo()
            << " | Artista: " << canciones[i].obtenerArtista()
            << " | Album: " << canciones[i].obtenerAlbum()
            << " | Duracion: " << canciones[i].obtenerDuracion() << "s\n";
    }
}

int AdministradorDeCancion::obtenerCantidad() const {
    return cantidad;
}

Cancion* AdministradorDeCancion::buscarCancion(const string& titulo) {
    for (int i = 0; i < cantidad; ++i)
        if (canciones[i].obtenerTitulo() == titulo)
            return &canciones[i];
    return nullptr;
}