#pragma once
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};