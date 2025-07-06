#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <string> 
#include "ListaReproduccion.h"
#include "Podcast.h"


using namespace std;

const int MAX_LISTAS_REPRODUCCION = 100; // Definir un tamaño máximo para las listas de reproducción
static const int MAX_PODCASTS = 50;

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    ListaReproduccion misListaReproducciones[MAX_LISTAS_REPRODUCCION]; // Usar un arreglo estático
    Podcast podcasts[MAX_PODCASTS];
    int numPodcasts;
    int numListas; // Contador de listas de reproducción
public:
    Usuario();
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario);
    string obtenerNombre() const;
    string obtenerCorreo() const;
    string obtenerContrasena() const;
    ListaReproduccion* obtenerListaReproduccion(); 
    const ListaReproduccion& obtenerListaReproduccion(int indice) const;
    int obtenerCantidadListas() const;

    void crearListaReproduccion(const ListaReproduccion& nuevaListaReproduccion);
    void eliminarListaReproduccion(const string& nombreListaReproduccion);
    void agregarPodcast(Podcast& p);
    Podcast obtenerPodcast(int indice) const;
    int obtenerCantidadPodcasts() const;
};

#endif