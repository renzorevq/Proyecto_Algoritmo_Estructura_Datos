#pragma once
#include <string>
#include <iostream>
#include "Podcast.h"
class AdministradorPodcast {
private:
    static const int MAX_PODCASTS = 50;
    Podcast podcasts[MAX_PODCASTS];
    int total = 0;

public:
    bool registrarPodcast(const std::string& titulo, const std::string& creador, int duracion);
    void listarPodcasts() const;
    int obtenerCantidad() const;
};