    #pragma once
    #ifndef USUARIO_H
    #define USUARIO_H


    #include "ListaReproduccion.h"

    using namespace std;

    class Usuario {
        string nombre;
        string correo;
        string contrasena;
        vector<ListaReproduccion> misListaReproducciones;
    public:
        Usuario();
        Usuario(const string& nombreUsuario,
            const string& correoElectronico,
            const string& contrasenaUsuario);
        string obtenerNombre() const;
        string obtenerCorreo() const;
        string obtenerContrasena() const;
        vector<ListaReproduccion>& obtenerListaReproduccion();

        void crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion);

        void eliminarListaReproduccion(const string& nombreListaReproduccion);
    };

    #endif
