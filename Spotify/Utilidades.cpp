#include "Utilidades.h"
#include "iostream"

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
    if (seleccion) {
        cout << "| " << string(relleno, ' ') << "\033[0m" << texto << "\033[32m" << string(ancho - 4 - relleno - texto.size(), ' ') << " | \n";
    }
    else {
        cout << "|" << string(relleno, ' ') << texto << string(ancho - 2 - relleno - texto.size(), ' ') << "|\n";
    }
}

void dibujarCaja(const vector<string>& lineas, int ancho) {
    lineaHorizontal(ancho);
    for (const auto& linea : lineas) textoCentrado(linea, ancho);
    lineaHorizontal(ancho);
}

void dibujarCajaConSeleccion(const string opciones[], int seleccion, int ancho, int numOpciones, const string titulo) {
    lineaHorizontal(ancho);
    textoCentrado("", ancho);
    if (titulo != "") {
        textoCentrado(titulo, ancho);
        textoCentrado("", ancho);
    }
    for (int i = 0; i < numOpciones; ++i) {
        string texto = (i == seleccion ? "* " : "  ") + opciones[i] + (i == seleccion ? " *" : "  ");
        textoCentrado(texto, ancho, i == seleccion);
    }
    textoCentrado("", ancho);
    lineaHorizontal(ancho);
}
