#pragma once
#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <functional>
#include "./nodo.h"

using namespace std;

template <typename T>
class ListaEnlazada {
    Nodo<T>* cabeza;
public:
    ListaEnlazada();
    ~ListaEnlazada();
    
    void insertar(const T& valor);
    bool eliminar(const function<bool(const T&)>& criterio);
    bool estaVacia() const;
    void porCada(const function<void(const T&)>& accion) const;
    void limpiar();
};

#endif // !LISTA_ENLAZADA_H
