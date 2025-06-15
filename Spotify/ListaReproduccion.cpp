#include "ListaReproduccion.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

ListaReproduccion::ListaReproduccion()
    : nombre(""), descripcion(""), canciones() {
}

ListaReproduccion::ListaReproduccion(const string& n, const string& d)
    : nombre(n), descripcion(d), canciones() {
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
