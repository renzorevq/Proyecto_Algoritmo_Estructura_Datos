#pragma once
#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;

    Nodo(const T& valor);
};

#endif NODO_H