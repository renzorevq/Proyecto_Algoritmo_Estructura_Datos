#pragma once
#include "Nodo.h"

template <typename T>
class ListaEnlazada {
    Nodo<T>* cabeza;
public:
    ListaEnlazada();
    ~ListaEnlazada();
    void insertar(const T& valor);
    // Elimina el primer elemento que cumpla el criterio
    template <typename Pred>
    bool eliminar(const Pred& criterio);
    bool estaVacia() const noexcept;
    // Aplica una acción a cada elemento
    template <typename Func>
    void porCada(const Func& accion) const;
    void limpiar();
};

template <typename T>
ListaEnlazada<T>::ListaEnlazada() : cabeza(nullptr) {}
template <typename T>
ListaEnlazada<T>::~ListaEnlazada() { limpiar(); }
template <typename T>
void ListaEnlazada<T>::insertar(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    if (!cabeza) cabeza = nuevo;
    else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
}
template <typename T>
template <typename Pred>
bool ListaEnlazada<T>::eliminar(const Pred& criterio) {
    Nodo<T>* anterior = nullptr;
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (criterio(actual->dato)) {
            if (anterior) anterior->siguiente = actual->siguiente;
            else cabeza = actual->siguiente;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}
template <typename T>
bool ListaEnlazada<T>::estaVacia() const noexcept { return cabeza == nullptr; }
template <typename T>
template <typename Func>
void ListaEnlazada<T>::porCada(const Func& accion) const {
    Nodo<T>* actual = cabeza;
    while (actual) {
        accion(actual->dato);
        actual = actual->siguiente;
    }
}
template <typename T>
void ListaEnlazada<T>::limpiar() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
}