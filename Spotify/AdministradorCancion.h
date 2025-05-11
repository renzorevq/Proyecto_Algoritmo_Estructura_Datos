#pragma once
#ifndef ADMINISTRADORDECANCION_H
#define ADMINISTRADORDECANCION_H

#include "Cancion.h"
#include <iostream>
#include <string>

const int MAX_CANCIONES = 100;

class AdministradorDeCancion {
private:
    Cancion canciones[MAX_CANCIONES];
    int cantidad;

public:
    AdministradorDeCancion() {
        cantidad = 0;
    }

    // Agrega una canción si hay espacio
    bool agregarCancion(const Cancion& cancion) {
        if (cantidad < MAX_CANCIONES) {
            canciones[cantidad] = cancion;
            cantidad++;
            return true;
        }
        else {
            std::cout << "Error: No se puede agregar más canciones. Límite alcanzado.\n";
            return false;
        }
    }

    // Elimina canción por título
    bool eliminarCancion(const std::string& titulo) {
        for (int i = 0; i < cantidad; ++i) {
            if (canciones[i].obtenerTitulo() == titulo) {
                for (int j = i; j < cantidad - 1; ++j) {
                    canciones[j] = canciones[j + 1];
                }
                cantidad--;
                return true;
            }
        }
        return false;
    }

    // Lista todas las canciones
    void listarCanciones() const {
        if (cantidad == 0) {
            std::cout << "No hay canciones registradas.\n";
            return;
        }
        for (int i = 0; i < cantidad; ++i) {
            std::cout << "Cancion #" << (i + 1) << "\n";
            std::cout << " Titulo  : " << canciones[i].obtenerTitulo() << "\n";
            std::cout << " Artista : " << canciones[i].obtenerArtista() << "\n";
            std::cout << " Album   : " << canciones[i].obtenerAlbum() << "\n";
            std::cout << " Duracion: " << canciones[i].obtenerDuracion() << " segundos\n\n";
        }
    }

    // Devuelve la cantidad actual de canciones
    int obtenerCantidad() const {
        return cantidad;
    }

    // Buscar canción por título (devuelve puntero o nullptr)
    Cancion* buscarCancion(const std::string& titulo) {
        for (int i = 0; i < cantidad; ++i) {
            if (canciones[i].obtenerTitulo() == titulo) {
                return &canciones[i];
            }
        }
        return nullptr;
    }
};

#endif
