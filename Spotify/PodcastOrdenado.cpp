#include "PodcastOrdenado.h"
#include <iostream>

using namespace std;

PodcastOrdenado::PodcastOrdenado(int cap) : capacidad(cap), cantidad(0) {
    podcasts = new Podcast[capacidad];
}

PodcastOrdenado::~PodcastOrdenado() {
    delete[] podcasts;
}

void PodcastOrdenado::agregarPodcast(const Podcast& p) {
    if (cantidad < capacidad) {
        podcasts[cantidad++] = p;
    }
    else {
        cout << "Capacidad máxima alcanzada.\n";
    }
}

void PodcastOrdenado::mostrarPodcasts() const {
    for (int i = 0; i < cantidad; i++) {
        cout << "Título: " << podcasts[i].obtenerTitulo()
            << ", Creador: " << podcasts[i].obtenerCreador()
            << ", Duración: " << podcasts[i].obtenerDuracion() << "s\n";
    }
}

void PodcastOrdenado::ordenarPorTitulo() {
    for (int i = 1; i < cantidad; i++) {
        Podcast clave = podcasts[i];
        int j = i - 1;
        while (j >= 0 && podcasts[j].obtenerTitulo() > clave.obtenerTitulo()) {
            podcasts[j + 1] = podcasts[j];
            j--;
        }
        podcasts[j + 1] = clave;
    }
}

void PodcastOrdenado::ordenarPorCreador() {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (podcasts[j].obtenerCreador() > podcasts[j + 1].obtenerCreador()) {
                Podcast temp = podcasts[j];
                podcasts[j] = podcasts[j + 1];
                podcasts[j + 1] = temp;
            }
        }
    }
}
