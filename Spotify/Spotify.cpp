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
#include <map>

#include "./utils.h"
#include "./login.h"

using namespace std;

// Cola circular genérica (FIFO)
template <typename T, size_t N>
class ColaCircular {
    T datos[N];
    size_t inicio = 0, fin = 0, conteo = 0;
public:
    void encolar(const T& valor) {
        if (conteo < N) {
            datos[fin] = valor;
            fin = (fin + 1) % N;
            ++conteo;
        }
    }
    void desencolar() {
        if (conteo > 0) {
            inicio = (inicio + 1) % N;
            --conteo;
        }
    }
    T& frente() {
        if (conteo == 0) throw out_of_range("Cola vacia");
        return datos[inicio];
    }
    bool estaVacia() const { return conteo == 0; }
};

// Quick sort para vector de Cancion por duracion
void quickSortDuracion(vector<Cancion>& v, int izq, int der) {
    if (izq >= der) return;
    int piv = v[(izq + der) / 2].obtenerDuracion();   // <<< usa el getter
    int i = izq, j = der;
    while (i <= j) {
        while (v[i].obtenerDuracion() < piv) ++i;      // <<< getter
        while (v[j].obtenerDuracion() > piv) --j;      // <<< getter
        if (i <= j) swap(v[i++], v[j--]);
    }
    quickSortDuracion(v, izq, j);
    quickSortDuracion(v, i, der);
}


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

    map<int, function<void()>> acciones;
    acciones[1] = [&] { registrarse(usuarios); };
    acciones[2] = [&] { iniciarSesion(usuarios); };
    acciones[3] = [&] { ejecutando = false; };

    while (ejecutando) {
        limpiarPantalla();
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
