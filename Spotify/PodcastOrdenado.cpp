#include "PodcastOrdenado.h"
#include <iostream>
PodcastOrdenado::PodcastOrdenado(int capacidad) {
    this->capacidad = capacidad;
    cantidad = 0;
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
        cout << "Capacidad maxima alcanzada.\n";
    }
}
void PodcastOrdenado::mostrarPodcasts() const {
    for (int i = 0; i < cantidad; i++) {
        cout << "Titulo: " << podcasts[i].obtenerTitulo()
            << ", Creador: " << podcasts[i].obtenerCreador()
            << ", Duracion: " << podcasts[i].obtenerDuracion() << "s\n";
    }
}
void PodcastOrdenado::ordenarPorTitulo() {
    mergeSort(0, cantidad - 1, 0); // criterio 0: título
}
void PodcastOrdenado::ordenarPorCreador() {
    mergeSort(0, cantidad - 1, 1); // criterio 1: creador
}
void PodcastOrdenado::limpiar() {

    cantidad = 0;
}
void PodcastOrdenado::mergeSort(int inicio, int fin, int criterio) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;
        mergeSort(inicio, medio, criterio);
        mergeSort(medio + 1, fin, criterio);
        merge(inicio, medio, fin, criterio);
    }
}
void PodcastOrdenado::merge(int inicio, int medio, int fin, int criterio) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    Podcast* izquierda = new Podcast[n1];
    Podcast* derecha = new Podcast[n2];
    for (int i = 0; i < n1; i++)
        izquierda[i] = podcasts[inicio + i];
    for (int j = 0; j < n2; j++)
        derecha[j] = podcasts[medio + 1 + j];
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        bool condicion;
        if (criterio == 0) // título
            condicion = izquierda[i].obtenerTitulo() < derecha[j].obtenerTitulo();
        else               // creador
            condicion = izquierda[i].obtenerCreador() < derecha[j].obtenerCreador();
        if (condicion)
            podcasts[k++] = izquierda[i++];
        else
            podcasts[k++] = derecha[j++];
    }
    while (i < n1) podcasts[k++] = izquierda[i++];
    while (j < n2) podcasts[k++] = derecha[j++];
    delete[] izquierda;
    delete[] derecha;
}