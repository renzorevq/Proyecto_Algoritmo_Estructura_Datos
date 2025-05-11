#include "CompartirCancion.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

// Genera un string de 3 dígitos aleatorios
std::string CompartirCancion::generarCodigo() const {
    std::string codigo;
    for (int i = 0; i < 3; ++i) {
        codigo += char('0' + (std::rand() % 10));
    }
    return codigo;
}

std::string CompartirCancion::compartir(const std::string& titulo) {
    if (conteo >= MAX_COMPARTIDOS) return "";

    std::string codigo = generarCodigo();
    std::string link = "https://open.spotify.com/intl-es/track/" + codigo;

    titulos[conteo] = titulo;
    links[conteo] = link;
    ++conteo;

    return link;
}

void CompartirCancion::listarCompartidos() const {
    std::cout << "=== Canciones Compartidas ===\n";
    if (conteo == 0) {
        std::cout << "(ninguna canción compartida aún)\n";
    }
    for (int i = 0; i < conteo; ++i) {
        std::cout << i + 1 << ". " << titulos[i]
            << " -> " << links[i] << "\n";
    }
    std::cout << "=============================\n";
}
