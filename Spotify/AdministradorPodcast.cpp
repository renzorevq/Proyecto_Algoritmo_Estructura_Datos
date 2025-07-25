#include "Podcast.h"
#include "AdministradorPodcast.h"
#include "PodcastOrdenado.h"



AdministradorPodcast::AdministradorPodcast() : ordenado(MAX_PODCASTS) {}
//Podcast
Podcast::Podcast() : titulo(""), creador(""), duracion(0) {}
Podcast::Podcast(const string& titulo, const string& creador, int duracion)
    : titulo(titulo), creador(creador), duracion(duracion) {
}
string Podcast::obtenerTitulo() const { return titulo; }
string Podcast::obtenerCreador() const { return creador; }
int Podcast::obtenerDuracion() const { return duracion; }

//PodcastManager
bool  AdministradorPodcast::registrarPodcast(const string& titulo, const string& creador, int duracion, Usuario& usuario) {
    if (total >= MAX_PODCASTS) return false;
    Podcast nuevoPodcast(titulo, creador, duracion);
    podcasts[total++] = nuevoPodcast;
    usuario.agregarPodcast(nuevoPodcast);
    return true;
}

void  AdministradorPodcast::listarPodcasts(Usuario& usuario) const {
    if (usuario.obtenerCantidadPodcasts() == 0) {
        cout << "(No hay podcasts registrados)\n";
        return;
    }
    for (int i = 0; i < usuario.obtenerCantidadPodcasts(); ++i) {
        cout << i + 1 << ". " << usuario.obtenerPodcast(i).obtenerTitulo()
            << " | Creador: " << usuario.obtenerPodcast(i).obtenerCreador()
            << " | Duracion: " << usuario.obtenerPodcast(i).obtenerDuracion() << "s\n";
    }
}

int  AdministradorPodcast::obtenerCantidad(Usuario& usuario) const {
    return usuario.obtenerCantidadPodcasts();
}

void AdministradorPodcast::ordenarPorTitulo() {
    for (int i = 1; i < total; ++i) {
        Podcast clave = podcasts[i];
        int j = i - 1;
        while (j >= 0 && podcasts[j].obtenerTitulo() > clave.obtenerTitulo()) {
            podcasts[j + 1] = podcasts[j];
            --j;
        }
        podcasts[j + 1] = clave;
    }
}

void AdministradorPodcast::ordenarPorCreador() {
    for (int i = 0; i < total - 1; ++i) {
        for (int j = 0; j < total - i - 1; ++j) {
            if (podcasts[j].obtenerCreador() > podcasts[j + 1].obtenerCreador()) {
                Podcast temp = podcasts[j];
                podcasts[j] = podcasts[j + 1];
                podcasts[j + 1] = temp;
            }
        }
    }
}

// Usar MergeSort por t�tulo
void AdministradorPodcast::ordenarPorTituloMerge() {
    ordenado.limpiar();
    for (int i = 0; i < total; ++i) {
        ordenado.agregarPodcast(podcasts[i]);
    }
    ordenado.ordenarPorTitulo();
    ordenado.mostrarPodcasts();
}

// Usar MergeSort por creador
void AdministradorPodcast::ordenarPorCreadorMerge() {
    for (int i = 0; i < total; ++i) {
        ordenado.agregarPodcast(podcasts[i]);
    }
    ordenado.ordenarPorCreador();
    ordenado.mostrarPodcasts();
}