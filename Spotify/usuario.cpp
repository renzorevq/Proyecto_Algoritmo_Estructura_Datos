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

//  Versión sin algorithm ni lambdas
void Usuario::eliminarListaReproduccion(const string& nombreListaReproduccion) {
    for (size_t i = 0; i < misListaReproducciones.size(); ++i) {
        if (misListaReproducciones[i].obtenerNombre() == nombreListaReproduccion) {
            // Sobreescribimos con el último y hacemos pop_back
            misListaReproducciones[i] = misListaReproducciones.back();
            misListaReproducciones.pop_back();
            break;  // Eliminamos solo la primera coincidencia
        }
    }
}
