#include <string>
#include <vector>
#include "./playlist.h"

using namespace std;

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    vector<Playlist> misPlaylists;
public:
    Usuario() {}
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario)
        : nombre(nombreUsuario), correo(correoElectronico), contrasena(contrasenaUsuario) {
    }
    string obtenerNombre() const { return nombre; }
    string obtenerCorreo() const { return correo; }
    string obtenerContrasena() const { return contrasena; }
    vector<Playlist>& obtenerPlaylists() { return misPlaylists; }
    void crearPlaylist(const Playlist& nuevaPlaylist) {
        misPlaylists.push_back(nuevaPlaylist);
    }
    void eliminarPlaylist(const string& nombrePlaylist) {
        misPlaylists.erase(
            remove_if(
                misPlaylists.begin(),
                misPlaylists.end(),
                [&](const Playlist& p) { return p.obtenerNombre() == nombrePlaylist; }
            ),
            misPlaylists.end()
        );
    }
};