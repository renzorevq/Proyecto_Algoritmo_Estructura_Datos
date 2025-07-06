#include "TablaHashUsuarios.h"
#include <iostream>

using namespace std;

int TablaHashUsuarios::hash(const string& correo) {
    int suma = 0;
    for (char c : correo)
        suma += c;
    return suma % HASH_SIZE;
}

TablaHashUsuarios::TablaHashUsuarios() {
    for (int i = 0; i < HASH_SIZE; ++i)
        tabla[i] = nullptr;
}

void TablaHashUsuarios::insertar(const Usuario& u) {
    auto* nuevo = new Nodo<Usuario>(u);
    int indice = hash(u.obtenerCorreo());
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
}

Usuario* TablaHashUsuarios::buscar(const string& correo) {
    int indice = hash(correo);
    Nodo<Usuario>* actual = tabla[indice];
    while (actual != nullptr) {
        if (actual->dato.obtenerCorreo() == correo)
            return &actual->dato;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool TablaHashUsuarios::eliminar(const string& correo) {
    int indice = hash(correo);
    Nodo<Usuario>* actual = tabla[indice];
    Nodo<Usuario>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->dato.obtenerCorreo() == correo) {
            if (anterior == nullptr)
                tabla[indice] = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

void TablaHashUsuarios::mostrar() {
   
    cout << "\n=== Tabla Hash de Usuarios ===\n";
    for (int i = 0; i < HASH_SIZE; ++i) {
        cout << "[" << i << "]: ";
        Nodo<Usuario>* actual = tabla[i];
        while (actual != nullptr) {
            cout << "(" << actual->dato.obtenerCorreo() << ", " << actual->dato.obtenerNombre() << ") -> ";
            actual = actual->siguiente;
        }
        cout << "nullptr\n";
    }
    
}
