#pragma once
#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};

const int MAX_GRAFO = 50;

