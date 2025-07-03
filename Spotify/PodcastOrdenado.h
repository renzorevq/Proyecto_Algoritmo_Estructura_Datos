#pragma once
#include "Podcast.h"

class PodcastOrdenado {
private:
    Podcast* podcasts;
    int capacidad;
    int cantidad;

    void mergeSort(int inicio, int fin, int criterio);
    void merge(int inicio, int medio, int fin, int criterio);
public:
    PodcastOrdenado(int capacidad);
    ~PodcastOrdenado();

    void agregarPodcast(const Podcast& p);
    void mostrarPodcasts() const;

    void ordenarPorTitulo();
    void ordenarPorCreador();
    void limpiar();


};
