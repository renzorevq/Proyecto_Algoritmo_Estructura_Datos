#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include "./ListaReproduccion.h"

using namespace std;

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    vector<Playlist> misPlaylists;
public:
    Usuario();
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario);
    string obtenerNombre() const;
    string obtenerCorreo() const;
    string obtenerContrasena() const;
    vector<Playlist>& obtenerPlaylists();

    void crearPlaylist(const Playlist& nuevaPlaylist);

    void eliminarPlaylist(const string& nombrePlaylist);
};

#endif // !USUARIO_H
