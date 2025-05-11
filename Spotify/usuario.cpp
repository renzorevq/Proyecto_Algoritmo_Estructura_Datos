#include <string>
#include <vector>

#include "./Playlist.h"
#include "./Usuario.h"

using namespace std;

Usuario::Usuario() {}
Usuario::Usuario(const string& nombreUsuario,
	const string& correoElectronico,
	const string& contrasenaUsuario)
	: nombre(nombreUsuario), correo(correoElectronico), contrasena(contrasenaUsuario) {
}

string Usuario::obtenerNombre() const { return nombre; }

string Usuario::obtenerCorreo() const { return correo; }
string Usuario::obtenerContrasena() const { return contrasena; }
vector<Playlist>& Usuario::obtenerPlaylists() { return misPlaylists; }
void Usuario::crearPlaylist(const Playlist& nuevaPlaylist) {
	misPlaylists.push_back(nuevaPlaylist);
}
void Usuario::eliminarPlaylist(const string& nombrePlaylist) {
	misPlaylists.erase(
		remove_if(
			misPlaylists.begin(),
			misPlaylists.end(),
			[&](const Playlist& p) { return p.obtenerNombre() == nombrePlaylist; }
		),
		misPlaylists.end()
	);
}
