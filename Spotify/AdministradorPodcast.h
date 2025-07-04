#pragma once


#include "Podcast.h"
#include "PodcastOrdenado.h"
using namespace std;
class AdministradorPodcast {
private:
    static const int MAX_PODCASTS = 50;
    Podcast podcasts[MAX_PODCASTS];
    int total = 0;
    PodcastOrdenado ordenado;

public:
    AdministradorPodcast();

    bool registrarPodcast(const string& titulo, const string& creador, int duracion);
    void listarPodcasts() const;
    int obtenerCantidad() const;

    void ordenarPorTitulo();    // Inserción
    void ordenarPorCreador();   // Burbuja    

    void ordenarPorTituloMerge();   //  MergeSort
    void ordenarPorCreadorMerge();  //  MergeSort

    const Podcast* obtenerTodos() const {
        return podcasts;
    }


};

