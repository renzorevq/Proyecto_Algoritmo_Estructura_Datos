#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <string> 
#include "ListaReproduccion.h"


using namespace std;

const int MAX_LISTAS_REPRODUCCION = 100; // Definir un tama�o m�ximo para las listas de reproducci�n

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    ListaReproduccion misListaReproducciones[MAX_LISTAS_REPRODUCCION]; // Usar un arreglo est�tico
    int numListas; // Contador de listas de reproducci�n
public:
    Usuario();
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario);
    string obtenerNombre() const;
    string obtenerCorreo() const;
    string obtenerContrasena() const;
    ListaReproduccion* obtenerListaReproduccion(); // Declaraci�n
    const ListaReproduccion& obtenerListaReproduccion(int indice) const;
    int obtenerCantidadListas() const; // Declaraci�n

    void crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion);
    void eliminarListaReproduccion(const string& nombreListaReproduccion);
};

#endif