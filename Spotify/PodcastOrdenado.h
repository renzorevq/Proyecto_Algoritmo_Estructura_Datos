#pragma once
#include "Podcast.h"

class PodcastOrdenado {
private:
    Podcast* podcasts;
    int capacidad;
    int cantidad;

public:
    PodcastOrdenado(int capacidad);
    ~PodcastOrdenado();

    void agregarPodcast(const Podcast& p);
    void mostrarPodcasts() const;

    void ordenarPorTitulo();
    void ordenarPorCreador();
};
