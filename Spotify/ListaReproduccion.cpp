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
    string lineas[2]; // Crear un arreglo para las líneas
    lineas[0] = "PLAYLIST: " + nombre;
    lineas[1] = descripcion;

    dibujarCaja(lineas, 2); // Pasar el arreglo y el número de líneas

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

ListaEnlazada<Cancion>& ListaReproduccion::obtenerCanciones() {
    return canciones;
}
