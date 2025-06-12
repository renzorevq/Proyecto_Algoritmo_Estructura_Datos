#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <string>
#include <map>
#include "utilidades.h"
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
int main() {
    vector<Usuario> usuarios;
    cargarUsuarios(usuarios);
    ColaCircular<Cancion, 100> colaReproduccion;


    bool ejecutando = true;
    map<int, function<void()>> acciones;
    acciones[1] = [&] { registrarse(usuarios); };
    acciones[2] = [&] { iniciarSesion(usuarios); };
    acciones[3] = [&] { ejecutando = false; };

    while (ejecutando) {
        limpiarPantalla();
        cout << "\033[32m";
        dibujarCaja({ "MINI SPOTIFY", "1. Registrarse", "2. Iniciar Sesion", "3. Salir" });
        cout << "Seleccione opcion: ";
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (acciones.count(opcion)) acciones[opcion]();
    }

    guardarUsuarios(usuarios);
    return 0;
}
