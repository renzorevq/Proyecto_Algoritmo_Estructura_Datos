#include <iostream>
#include <conio.h>
#include <string>
#include "Utilidades.h"
#include "Login.h"
#include "Cancion.h"
#include "ColaCircular.h"
#include "ListaEnlazada.h"
#include <windows.h>
#include "ListaReproduccion.h"

using namespace std;

template <typename T>
class Pila {
    T elementos[100]; 
    int tope = 0;
public:
    void push(const T& valor) {
        if (tope < 100) elementos[tope++] = valor;
    }
    void pop() {
        if (tope > 0) tope--;
        else throw out_of_range("Pila vacia");
    }
    T& top() {
        if (tope == 0) throw out_of_range("Pila vacia");
        return elementos[tope - 1];
    }
    bool estaVacia() const { return tope == 0; }
};

// Función para leer opción como template
template <typename T>
T leerOpcionMenu(const int numOpciones) {
    string entrada;
    while (true) {
        cout << "Seleccione opcion: ";
        getline(cin, entrada);
        if (entrada.empty()) {
            cout << "ERROR: Ingrese un valor valido\n";
            continue;
        }
        bool esDigito = true;
        for (char c : entrada) {
            if (!isdigit(c)) { esDigito = false; break; }
        }
        if (!esDigito) {
            cout << "ERROR: Ingrese un valor valido\n";
            continue;
        }
        T opcion = static_cast<T>(stoi(entrada));
        if (opcion >= 1 && opcion <= numOpciones) return opcion;
        cout << "ERROR: Opcion fuera de rango\n";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Arreglo de usuarios tradicional
    Usuario* usuarios = new Usuario[MAX_USUARIOS];
    int numUsuarios = 0;

    cargarUsuarios(usuarios, numUsuarios);
    cargarPlaylists(usuarios, numUsuarios);
    cargarCanciones(usuarios, numUsuarios);
    cargarPodcasts(usuarios, numUsuarios);

   
    ColaCircular<Cancion, 100> colaReproduccion;

    const char* opcionesMenu[] = {
        "1. Registrarse",
        "2. Iniciar Sesion",
        "3. Salir"
    };
    const int numOpciones = 3;
    int seleccion = 0;
    bool ejecutando = true;

    while (ejecutando) {
        limpiarPantalla();

        
        cout << "+----------------------------------+\n";
        cout << "|          MINI SPOTIFY            |\n";
        cout << "+----------------------------------+\n";
        for (int i = 0; i < numOpciones; i++) {
            if (i == seleccion)
                cout << ">> " << opcionesMenu[i] << "\n";
            else
                cout << "   " << opcionesMenu[i] << "\n";
        }

        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) seleccion = (seleccion + numOpciones - 1) % numOpciones;
            else if (tecla == 80) seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13) {
            switch (seleccion + 1) {
            case 1:
                registrarse(usuarios, numUsuarios);
                break;
            case 2:
                iniciarSesion(usuarios, numUsuarios);
                break;
            case 3:
                ejecutando = false;
                break;
            }
        }
    }

    guardarUsuarios(usuarios, numUsuarios);
    guardarPlaylists(usuarios, numUsuarios);
    guardarCanciones(usuarios, numUsuarios);
    guardarPodcasts(usuarios, numUsuarios);
    delete[] usuarios;
    cout << "\nGracias por usar Mini Spotify!\n";
    return 0;
}