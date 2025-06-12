#pragma once
#include <string>
#include <iostream>
#include "Podcast.h"
using namespace std;
class AdministradorPodcast {
private:
    static const int MAX_PODCASTS = 50;
    Podcast podcasts[MAX_PODCASTS];
    int total = 0;

public:
    bool registrarPodcast(const string& titulo, const string& creador, int duracion);
    void listarPodcasts() const;
    int obtenerCantidad() const;

    void ordenarPorTitulo();    // Inserción
    void ordenarPorCreador();   // Burbuja    
    const Podcast* obtenerTodos() const {
        return podcasts;
    }


};

