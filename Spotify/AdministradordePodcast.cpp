#include "Podcast.h"
#include "AdministradordePodcast.h"
// --- Podcast ---
Podcast::Podcast() : titulo(""), creador(""), duracion(0) {}
Podcast::Podcast(const std::string& titulo, const std::string& creador, int duracion)
    : titulo(titulo), creador(creador), duracion(duracion) {
}

std::string Podcast::obtenerTitulo() const { return titulo; }
std::string Podcast::obtenerCreador() const { return creador; }
int Podcast::obtenerDuracion() const { return duracion; }

// --- PodcastManager ---
bool AdministradordePodcast::registrarPodcast(const std::string& titulo, const std::string& creador, int duracion) {
    if (total >= MAX_PODCASTS) return false;
    podcasts[total++] = Podcast(titulo, creador, duracion);
    return true;
}

void AdministradordePodcast::listarPodcasts() const {
    if (total == 0) {
        std::cout << "(No hay podcasts registrados)\n";
        return;
    }
    for (int i = 0; i < total; ++i) {
        std::cout << i + 1 << ". " << podcasts[i].obtenerTitulo()
            << " | Creador: " << podcasts[i].obtenerCreador()
            << " | Duración: " << podcasts[i].obtenerDuracion() << "s\n";
    }
}

int AdministradordePodcast::obtenerCantidad() const {
    return total;
}
