#include <string>
#include <vector>
#include "Playlist.h"
#include "Usuario.h"
#include "Cancion.h"


Usuario::Usuario() {}
Usuario::Usuario(const string& nombreUsuario,
	const string& correoElectronico,
	const string& contrasenaUsuario)
	: nombre(nombreUsuario), correo(correoElectronico), contrasena(contrasenaUsuario) {
}

string Usuario::obtenerNombre() const { return nombre; }

string Usuario::obtenerCorreo() const { return correo; }
string Usuario::obtenerContrasena() const { return contrasena; }
vector<ListaReproduccion>& Usuario::obtenerListaReproduccion() { return misListaReproducciones; }
void Usuario::crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion) {
	misListaReproducciones.push_back(nuevaListaReproduccion);
}
void Usuario::eliminarListaReproduccion(const string& nombreListaReproduccion) {
	misListaReproducciones.erase(
		remove_if(
			misListaReproducciones.begin(),
			misListaReproducciones.end(),
			[&](const ListaReproduccion& p) { return p.obtenerNombre() == nombreListaReproduccion; }
		),
		misListaReproducciones.end()
	);
}
