#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <string> 
#include "ListaReproduccion.h"


using namespace std;

const int MAX_LISTAS_REPRODUCCION = 100; // Definir un tamaño máximo para las listas de reproducción

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    ListaReproduccion misListaReproducciones[MAX_LISTAS_REPRODUCCION]; // Usar un arreglo estático
    int numListas; // Contador de listas de reproducción
public:
    Usuario();
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario);
    string obtenerNombre() const;
    string obtenerCorreo() const;
    string obtenerContrasena() const;
    ListaReproduccion* obtenerListaReproduccion(); // Declaración
    const ListaReproduccion& obtenerListaReproduccion(int indice) const;
    int obtenerCantidadListas() const; // Declaración

    void crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion);
    void eliminarListaReproduccion(const string& nombreListaReproduccion);
};

#endif