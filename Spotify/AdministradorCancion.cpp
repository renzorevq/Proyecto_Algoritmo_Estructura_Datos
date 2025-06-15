
#include "AdministradorCancion.h"
#include <iostream>
using namespace std;

bool AdministradorCancion::agregarCancion(const Cancion& cancion) {
    if (cantidad >= MAX_CANCIONES) {
        cout << "Error: límite de canciones alcanzado.\n";
        return false;
    }
    canciones[cantidad++] = cancion;
    return true;
}

bool AdministradorCancion::eliminarCancion(const string& titulo) {
    for (int i = 0; i < cantidad; ++i) {
        if (canciones[i].obtenerTitulo() == titulo) {
            for (int j = i; j < cantidad - 1; ++j)
                canciones[j] = canciones[j + 1];
            --cantidad;
            return true;
        }
    }
    return false;
}

void AdministradorCancion::listarCanciones() const {
    if (cantidad == 0) {
        cout << "No hay canciones registradas.\n";
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        const Cancion& c = canciones[i];
        cout << i + 1 << ". " << c.obtenerTitulo()
            << " | Artista: " << c.obtenerArtista()
            << " | Álbum: " << c.obtenerAlbum()
            << " | Duración: " << c.obtenerDuracion()
            << "s\n";
    }
}

int AdministradorCancion::obtenerCantidad() const {
    return cantidad;
}

Cancion* AdministradorCancion::buscarCancion(const string& titulo) {
    for (int i = 0; i < cantidad; ++i)
        if (canciones[i].obtenerTitulo() == titulo)
            return &canciones[i];
    return nullptr;
}
