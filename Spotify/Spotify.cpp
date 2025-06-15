#include <iostream>
#include <conio.h>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <string>
#include <map>
#include "Utilidades.h"
#include "Login.h"
#include "Cancion.h"
#include "ColaCircular.h"
#include "ListaEnlazada.h"
using namespace std;

template <typename T>
class Pila {
    vector<T> elementos;
public:
    void push(const T& valor) { elementos.push_back(valor); }
    void pop() {
        if (elementos.empty()) throw out_of_range("Pila vacia");
        elementos.pop_back();
    }
    T& top() {
        if (elementos.empty()) throw out_of_range("Pila vacia");
        return elementos.back();
    }
    bool estaVacia() const { return elementos.empty(); }
};

// Funci�n para leer opci�n v�lida del men� principal
int leerOpcionMenu() {
    string entrada;
    int opcion;

    while (true) {
        cout << "Seleccione opcion: ";
        getline(cin, entrada);

        // Verificar si la entrada est� vac�a
        if (entrada.empty()) {
            cout << "ERROR: Ingrese un valor valido\n";
            continue;
        }

        // Verificar si todos los caracteres son d�gitos
        bool esValido = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (esValido) {
            try {
                opcion = stoi(entrada);
                if (opcion >= 1 && opcion <= 3) {
                    return opcion;
                }
                else {
                    cout << "ERROR: Ingrese un valor valido\n";
                }
            }
            catch (const exception&) {
                cout << "ERROR: Ingrese un valor valido\n";
            }
        }
        else {
            cout << "ERROR: Ingrese un valor valido\n";
        }
    }
}

int main() {
    vector<Usuario> usuarios;
    cargarUsuarios(usuarios);
    ColaCircular<Cancion, 100> colaReproduccion;
    bool ejecutando = true;
    vector<string> opcionesMenu = {
        "Registrarse",
        "Iniciar Sesion",
        "Salir"
    };
    int seleccion = 0;

    map<int, function<void()>> acciones;
    acciones[1] = [&] { registrarse(usuarios); };
    acciones[2] = [&] { iniciarSesion(usuarios); };
    acciones[3] = [&] { ejecutando = false; };

    while (ejecutando) {
        limpiarPantalla();
        cout << "\033[32m";
        dibujarCajaConSeleccion(opcionesMenu, seleccion, 40);
       /* dibujarCaja({
            "MINI SPOTIFY CON QUICKSORT",
            "1. Registrarse",
            "2. Iniciar Sesion",
            "3. Salir"
            });*/
       /* cout << "Seleccione opcion: ";
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (acciones.count(opcion)) {
            acciones[opcion]();
        }
        else {
            cout << "Opcion no valida!\n";
            cout << "Presione Enter para continuar...";
            cin.get();
        }*/
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) seleccion = (seleccion - 1 + opcionesMenu.size()) % opcionesMenu.size(); // ↑
            if (tecla == 80) seleccion = (seleccion + 1) % opcionesMenu.size(); // ↓
        }
        else if (tecla == 13) {
            int opcion = seleccion + 1;
            acciones[opcion]();
        }
    }

    guardarUsuarios(usuarios);
    cout << "\n�Gracias por usar Mini Spotify!\n";
    return 0;
}