//#include "pch.h"
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <string>

#include "./utils.h"
#include "./login.h"

using namespace std;

// Pila genérica (LIFO)
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

// Cola genérica (FIFO)
template <typename T>
class Cola {
    list<T> elementos;
public:
    void encolar(const T& valor) { elementos.push_back(valor); }
    void desencolar() {
        if (elementos.empty()) throw out_of_range("Cola vacia");
        elementos.pop_front();
    }
    T& frente() {
        if (elementos.empty()) throw out_of_range("Cola vacia");
        return elementos.front();
    }
    bool estaVacia() const { return elementos.empty(); }
};

// Persistencia de usuarios
void cargarUsuarios(vector<Usuario>& usuarios) {
    ifstream archivo("usuarios.txt");
    string linea;
    while (getline(archivo, linea)) {
        string nombreUsuario, correoElectronico, contrasenaUsuario;
        stringstream ss(linea);
        getline(ss, nombreUsuario, ',');
        getline(ss, correoElectronico, ',');
        getline(ss, contrasenaUsuario, ',');
        usuarios.emplace_back(nombreUsuario, correoElectronico, contrasenaUsuario);
    }
}

void guardarUsuarios(const vector<Usuario>& usuarios) {
    ofstream archivo("usuarios.txt");
    for (const auto& u : usuarios) {
        archivo << u.obtenerNombre() << ","
            << u.obtenerCorreo() << ","
            << u.obtenerContrasena() << "\n";
    }
}

int main() {
    vector<Usuario> usuarios;
    cargarUsuarios(usuarios);
    bool ejecutando = true;

    while (ejecutando) {
        limpiarPantalla();
        dibujarCaja({ "MINI SPOTIFY", "1. Registrarse", "2. Iniciar Sesion", "3. Salir" });
        cout << "Seleccione opcion: ";
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (opcion)
        {
        case 1:
            registrarse(usuarios);
            break;
        case 2:
            iniciarSesion(usuarios);
            break;
        case 3:
            ejecutando = false;
            break;
        default:
            break;
        }
    }
    guardarUsuarios(usuarios);
    return 0;
}
