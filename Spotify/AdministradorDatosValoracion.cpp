#include "AdministradorDatosValoracion.h"
#include "DatosValoracion.h"
#include <iostream>

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

void DatosValoracion::listarPromediosOrdenado() const {
    cout << "=== Valoraciones Promedio Ordenado (Counting Sort) ===\n";
    if (conteo == 0) {
        cout << "(sin valoraciones aun)\n";
    }
    else {
        // Matriz de titulos agrupados por valor promedio (1 al 5)
        string agrupados[6][MAX_TITULOS];  // 0 no se usa
        int cantidadPorValor[6] = { 0 };   // cantidad por cada fila

        for (int i = 0; i < conteo; ++i) {
            int promedioEntero = sumaValoracion[i] / cantidadValoraciones[i];
            int pos = cantidadPorValor[promedioEntero];
            if (pos < MAX_TITULOS) {
                agrupados[promedioEntero][pos] = titulos[i];
                cantidadPorValor[promedioEntero]++;
            }
        }

        for (int i = 5; i >= 1; --i) {
            for (int j = 0; j < cantidadPorValor[i]; ++j) {
                cout << agrupados[i][j] << " -> " << i << "/5\n";
            }
        }
    }
    cout << "=============================\n";
}
