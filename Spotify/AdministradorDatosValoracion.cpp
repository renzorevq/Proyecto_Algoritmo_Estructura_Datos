#include "AdministradorDatosValoracion.h"
#include "DatosValoracion.h"
#include <iostream>
#include <iomanip>

bool DatosValoracion::agregarValoracion(const string& titulo, int valor) {
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

float DatosValoracion::obtenerPromedio(const string& titulo) const {
    for (int i = 0; i < conteo; ++i) {
        if (titulos[i] == titulo && cantidadValoraciones[i] > 0) {
            return (float)sumaValoracion[i] / cantidadValoraciones[i];
        }
    }
    return 0.0f;
}

void DatosValoracion::listarPromedios() const {
    cout << "=== Valoraciones Promedio ===\n";
    if (conteo == 0) {
        cout << "(sin valoraciones aun)\n";
    }
    else {
        for (int i = 0; i < conteo; ++i) {
            
            int promedioEntero = sumaValoracion[i] / cantidadValoraciones[i];
            cout << titulos[i] << " -> " << promedioEntero << "/5\n";
        }
    }
    cout << "=============================\n";
}
