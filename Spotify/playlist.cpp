#include <iostream>
#include <string>

#include "./playlist.h"
#include "./listaEnlazada.h"
#include "./cancion.h"
#include "./utils.h"

using namespace std;

Playlist::Playlist() {};
Playlist::Playlist(const string& nombrePlaylist, const string& descripcionPlaylist)
	: nombre(nombrePlaylist), descripcion(descripcionPlaylist) {
}

void Playlist::agregarCancion(const Cancion& cancion) {
	canciones.insertar(cancion);
}

void Playlist::eliminarCancion(const string& tituloCancion) { 
	canciones.eliminar([&](const Cancion& c) {
		return c.obtenerTitulo() == tituloCancion;
		});
}

void Playlist::listarCanciones() const {
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

string Playlist::obtenerNombre() const { return nombre; }
