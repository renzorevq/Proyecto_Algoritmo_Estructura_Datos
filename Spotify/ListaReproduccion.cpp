#include <iostream>
#include <string>
#include "ListaReproduccion.h"
#include "ListaEnlazada.h"
#include "Cancion.h"
#include "Utilidades.h"

ListaReproduccion::ListaReproduccion() {};
ListaReproduccion::ListaReproduccion(const string& nombrePlaylist, const string& descripcionPlaylist)
	: nombre(nombrePlaylist), descripcion(descripcionPlaylist) {
}

void ListaReproduccion::agregarCancion(const Cancion& cancion) {
	canciones.insertar(cancion);
}

void ListaReproduccion::eliminarCancion(const string& tituloCancion) {
	canciones.eliminar([&](const Cancion& c) {
		return c.obtenerTitulo() == tituloCancion;
		});
}

void ListaReproduccion::listarCanciones() const {
	dibujarCaja({ "PLAYLIST: " + nombre, descripcion });
	if (canciones.estaVacia()) {
		cout << "(sin canciones)" << "\n";
	}
	else {
		canciones.porCada([&](const Cancion& c) {
			cout << "- " << c.obtenerTitulo() << " - " << c.obtenerArtista() << "\n";
			});
	}
}

string ListaReproduccion::obtenerNombre() const { return nombre; }
