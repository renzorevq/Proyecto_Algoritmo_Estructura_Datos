#pragma once

using namespace std;
template <typename T>
class Nodo {
public:
	T dato;
	Nodo* siguiente;

	Nodo(const T& valor);
};


template <typename T>
Nodo<T>::Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}

