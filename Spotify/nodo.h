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


template <typename T>
Nodo<T>::Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}

#endif NODO_H