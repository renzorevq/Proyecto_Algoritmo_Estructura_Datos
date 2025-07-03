#include "Utilidades.h"
#include <iostream>

using namespace std;

// Utilidades de consola
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\n[ENTER] para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Dibuja caja ASCII
void lineaHorizontal(int ancho) {
    cout << "+" << string(ancho - 2, '-') << "+\n";
}

void textoCentrado(const string& texto, int ancho, bool seleccion) {
    int relleno = (ancho - texto.size()) / 2;
    cout << "|" << string(relleno, ' ') << texto << string(ancho - 2 - relleno - texto.size(), ' ') << "|\n";
}

void dibujarCaja(const string lineas[], int numLineas, int ancho) {
    lineaHorizontal(ancho);
    for (int i = 0; i < numLineas; ++i) {
        textoCentrado(lineas[i], ancho, false);
    }
    lineaHorizontal(ancho);
}

void dibujarCajaConSeleccion(const string opciones[], int seleccion, int ancho, int numOpciones, const string titulo) {
    lineaHorizontal(ancho);
    textoCentrado("", ancho);
    if (!titulo.empty()) {
        textoCentrado(titulo, ancho, false);
        textoCentrado("", ancho);
    }
    for (int i = 0; i < numOpciones; ++i) {
        string texto = (i == seleccion ? "* " : "  ") + opciones[i] + (i == seleccion ? " *" : "  ");
        textoCentrado(texto, ancho, false);
    }
    textoCentrado("", ancho);
    lineaHorizontal(ancho);
}
