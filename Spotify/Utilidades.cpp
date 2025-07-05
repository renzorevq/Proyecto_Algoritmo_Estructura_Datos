#include "Utilidades.h"
#include <iostream>

using namespace std;

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

// Dibuja caja ALlamada recursivaSCII
void lineaHorizontal(int ancho) {
    cout << "+" << string(ancho - 2, '-') << "+\n";
}

void textoCentrado(const string& texto, int ancho, bool seleccion) { // No se define el argumento predeterminado aquí
    int relleno = (ancho - texto.size()) / 2;
    cout << "|" << string(relleno, ' ') << texto << string(ancho - 2 - relleno - texto.size(), ' ') << "|\n";
}

void dibujarCaja(const string lineas[], int numLineas, int ancho) {
    lineaHorizontal(ancho);
    for (int i = 0; i < numLineas; ++i)
        textoCentrado(lineas[i], ancho, false);
    lineaHorizontal(ancho);
}

void dibujarCajaConSeleccion(const string opciones[], int seleccion,
    int ancho, int numOpciones, const string titulo) {
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
int leerEntero(const string& mensaje) {
    string entrada;
    int resultado = 0;
    bool valido = false;

    while (!valido) {
        cout << mensaje;
        getline(cin, entrada);

        if (entrada.empty()) {
            cout << "ERROR: Entrada vacía.\n";
            continue;
        }

        bool negativo = false;
        int i = 0;

        if (entrada[0] == '-') {
            negativo = true;
            i = 1;
        }

        resultado = 0;
        valido = true;

        for (; i < entrada.length(); ++i) {
            if (!isdigit(entrada[i])) {
                valido = false;
                break;
            }
            resultado = resultado * 10 + (entrada[i] - '0');
        }

        if (!valido) {
            cout << "ERROR: Ingrese un número entero válido.\n";
            continue;
        }

        if (negativo) resultado *= -1;
    }

    return resultado;
}
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo) {
    int valor;

    while (true) {
        valor = leerEntero(mensaje);
        if (valor >= minimo && valor <= maximo)
            break;
        else
            cout << "ERROR: El número debe estar entre " << minimo << " y " << maximo << ".\n";
    }

    return valor;
}