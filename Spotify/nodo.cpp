#include "./nodo.h"

template <typename T>
Nodo<T>::Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}