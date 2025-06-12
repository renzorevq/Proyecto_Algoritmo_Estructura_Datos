#include "Cancion.h"
#include <iostream>
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

// — Implementación de Playlist —
ListaReproduccion::ListaReproduccion() : nombre(""), descripcion("") {}
ListaReproduccion::ListaReproduccion(const string& n, const string& d)
    : nombre(n), descripcion(d) {
}

void ListaReproduccion::agregarCancion(const Cancion& c) {
    canciones.insertar(c);
}

void ListaReproduccion::eliminarCancion(const string& tituloC) {
    canciones.eliminar([&](const Cancion& c) {
        return c.obtenerTitulo() == tituloC;
        });
}

void ListaReproduccion::listarCanciones() const {
    dibujarCaja({ "PLAYLIST: " + nombre, descripcion });
    if (canciones.estaVacia()) {
        cout << "(sin canciones)\n";
    }
    else {
        canciones.porCada([&](const Cancion& c) {
            cout << "- " << c.obtenerTitulo()
                << "  |  " << c.obtenerArtista() << "\n";
            });
    }
}

string ListaReproduccion::obtenerNombre() const {
    return nombre;
}


const ListaEnlazada<Cancion>& ListaReproduccion::obtenerCanciones() const {
    return canciones;
}
