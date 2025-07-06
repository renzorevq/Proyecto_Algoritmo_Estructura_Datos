#include "Usuario.h"

Usuario::Usuario() : numListas(0) {} // Inicializar el contador de listas

Usuario::Usuario(const string& nombreUsuario,
    const string& correoElectronico,
    const string& contrasenaUsuario)
    : nombre(nombreUsuario), correo(correoElectronico), contrasena(contrasenaUsuario), numListas(0) {
}

string Usuario::obtenerNombre() const { return nombre; }

string Usuario::obtenerCorreo() const { return correo; }

string Usuario::obtenerContrasena() const { return contrasena; }

ListaReproduccion* Usuario::obtenerListaReproduccion() {
    return misListaReproducciones; // Retornar el arreglo de listas
}

const ListaReproduccion& Usuario::obtenerListaReproduccion(int indice) const {
    return misListaReproducciones[indice];
}

int Usuario::obtenerCantidadListas() const{
    return numListas; // Retornar el número de listas
}

void Usuario::crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion) {
    if (numListas < MAX_LISTAS_REPRODUCCION) {
        misListaReproducciones[numListas++] = nuevaListaReproduccion; // Agregar la nueva lista
    }
}

void Usuario::eliminarListaReproduccion(const string& nombreListaReproduccion) {
    for (size_t i = 0; i < numListas; ++i) {
        if (misListaReproducciones[i].obtenerNombre() == nombreListaReproduccion) {
            // Sobreescribimos con el último y hacemos pop_back
            misListaReproducciones[i] = misListaReproducciones[--numListas]; // Reducir el contador
            break;  // Eliminamos solo la primera coincidencia
        }
    }
}