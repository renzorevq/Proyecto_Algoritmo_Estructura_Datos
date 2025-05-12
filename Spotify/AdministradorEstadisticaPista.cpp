#include "AdministradorEstadisticaPista.h"
#include "EstadisticaPista.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void EstadisticaPista::registrarReproduccion(const std::string& titulo) {
    for (int i = 0; i < cantidad; ++i) {
        if (titulos[i] == titulo) {
            conteos[i]++;
            return;
        }
    }

    if (cantidad < MAX_CANCIONES) {
        titulos[cantidad] = titulo;
        conteos[cantidad] = 1;
        cantidad++;
    }
}

void EstadisticaPista::mostrarEstadisticas() const {
    std::cout << "=== Estadísticas de Reproducción ===\n";
    if (cantidad == 0) {
        std::cout << "(aún no se han reproducido canciones)\n";
    }
    else {
        for (int i = 0; i < cantidad; ++i) {
            std::cout << std::setw(2) << (i + 1) << ". "
                << titulos[i] << " - "
                << conteos[i] << " reproducciones\n";
        }
    }
    std::cout << "====================================\n";
}
