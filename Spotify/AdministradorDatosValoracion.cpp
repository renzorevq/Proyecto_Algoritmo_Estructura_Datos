#include "AdministradorDatosValoracion.h"
#include "DatosValoracion.h"
#include <iostream>
#include <iomanip>

bool DatosValoracion::agregarValoracion(const std::string& titulo, int valor) {
    if (valor < 1 || valor > 5) return false;

    for (int i = 0; i < conteo; ++i) {
        if (titulos[i] == titulo) {
            sumaValoracion[i] += valor;
            cantidadValoraciones[i]++;
            return true;
        }
    }

    if (conteo >= MAX_VAL) return false;

    titulos[conteo] = titulo;
    sumaValoracion[conteo] = valor;
    cantidadValoraciones[conteo] = 1;
    conteo++;
    return true;
}

float DatosValoracion::obtenerPromedio(const std::string& titulo) const {
    for (int i = 0; i < conteo; ++i) {
        if (titulos[i] == titulo && cantidadValoraciones[i] > 0) {
            return (float)sumaValoracion[i] / cantidadValoraciones[i];
        }
    }
    return 0.0f;
}

void DatosValoracion::listarPromedios() const {
    std::cout << "=== Valoraciones Promedio ===\n";
    for (int i = 0; i < conteo; ++i) {
        float promedio = (float)sumaValoracion[i] / cantidadValoraciones[i];
        std::cout << std::fixed << std::setprecision(2);
        std::cout << titulos[i] << " -> " << promedio << "/5\n";
    }
    if (conteo == 0)
        std::cout << "(sin valoraciones aún)\n";
    std::cout << "=============================\n";
}
