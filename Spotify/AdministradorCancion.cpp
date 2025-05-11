#include <string>
#include "Cancion.h"
#include "AdministradorCancion.h"
using namespace std;

Cancion::Cancion() : titulo(""), artista(""), album(""), duracion(0) {}

Cancion::Cancion(const std::string& tituloCancion, const std::string& nombreArtista,
    const std::string& nombreAlbum, int duracionSegundos)
    : titulo(tituloCancion), artista(nombreArtista), album(nombreAlbum), duracion(duracionSegundos) {
}

std::string Cancion::obtenerTitulo() const { return titulo; }
std::string Cancion::obtenerArtista() const { return artista; }
std::string Cancion::obtenerAlbum() const { return album; }
int Cancion::obtenerDuracion() const { return duracion; }

// --- AdministradorDeCancion ---
bool AdministradorDeCancion::agregarCancion(const Cancion& cancion) {
    if (cantidad >= MAX_CANCIONES) {
        std::cout << "Error: No se puede agregar más canciones. Límite alcanzado.\n";
        return false;
    }
    canciones[cantidad++] = cancion;
    return true;
}

bool AdministradorDeCancion::eliminarCancion(const std::string& titulo) {
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
        std::cout << "No hay canciones registradas.\n";
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        std::cout << i + 1 << ". " << canciones[i].obtenerTitulo()
            << " | Artista: " << canciones[i].obtenerArtista()
            << " | Álbum: " << canciones[i].obtenerAlbum()
            << " | Duración: " << canciones[i].obtenerDuracion() << "s\n";
    }
}

int AdministradorDeCancion::obtenerCantidad() const {
    return cantidad;
}

Cancion* AdministradorDeCancion::buscarCancion(const std::string& titulo) {
    for (int i = 0; i < cantidad; ++i)
        if (canciones[i].obtenerTitulo() == titulo)
            return &canciones[i];
    return nullptr;
}