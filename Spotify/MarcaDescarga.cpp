#include "MarcaDescarga.h"

bool MarcaDescarga::registrarDescarga(const std::string& titulo) {
    for (int i = 0; i < cantidad; ++i) {
        if (titulos[i] == titulo) {
            conteoDescargas[i]++;
            return true;
        }
    }

    if (cantidad < MAX) {
        titulos[cantidad] = titulo;
        conteoDescargas[cantidad] = 1;
        cantidad++;
        return true;
    }

    return false; // No se pudo registrar
}

void MarcaDescarga::mostrarDescargas() const {
    std::cout << "\n=== CANCIONES DESCARGADAS ===\n";
    if (cantidad == 0) {
        std::cout << "(sin descargas todavía)\n";
    }
    else {
        for (int i = 0; i < cantidad; ++i) {
            std::cout << "- " << titulos[i] << " (descargada " << conteoDescargas[i] << " veces)\n";
        }
    }
    std::cout << "=============================\n";
}
