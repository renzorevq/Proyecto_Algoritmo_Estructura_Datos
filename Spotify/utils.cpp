#include "./Utils.h"
#include "iostream"
#include <string>

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

void textoCentrado(const string& texto, int ancho) {
    int relleno = (ancho - texto.size()) / 2;
    cout << "|" << string(relleno, ' ') << texto << string(ancho - 2 - relleno - texto.size(), ' ') << "|\n";
}

void dibujarCaja(const vector<string>& lineas, int ancho) {
    lineaHorizontal(ancho);
    for (const auto& linea : lineas) textoCentrado(linea, ancho);
    lineaHorizontal(ancho);
}