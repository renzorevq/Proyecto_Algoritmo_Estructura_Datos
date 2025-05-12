#include "Podcast.h"
#include "AdministradorPodcast.h"

using namespace std;

// --- Podcast ---
Podcast::Podcast() : titulo(""), creador(""), duracion(0) {}
Podcast::Podcast(const string& titulo, const string& creador, int duracion)
    : titulo(titulo), creador(creador), duracion(duracion) {
}

string Podcast::obtenerTitulo() const { return titulo; }
string Podcast::obtenerCreador() const { return creador; }
int Podcast::obtenerDuracion() const { return duracion; }

// --- PodcastManager ---
bool  AdministradorPodcast::registrarPodcast(const string& titulo, const string& creador, int duracion) {
    if (total >= MAX_PODCASTS) return false;
    podcasts[total++] = Podcast(titulo, creador, duracion);
    return true;
}

void  AdministradorPodcast::listarPodcasts() const {
    if (total == 0) {
        cout << "(No hay podcasts registrados)\n";
        return;
    }
    for (int i = 0; i < total; ++i) {
        cout << i + 1 << ". " << podcasts[i].obtenerTitulo()
            << " | Creador: " << podcasts[i].obtenerCreador()
            << " | Duracion: " << podcasts[i].obtenerDuracion() << "s\n";
    }
}

int  AdministradorPodcast::obtenerCantidad() const {
    return total;
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
