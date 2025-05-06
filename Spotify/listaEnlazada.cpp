#include <string>
#include <functional>

#include "./listaEnlazada.h"
#include "./nodo.h"

using namespace std;

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
bool ListaEnlazada<T>::eliminar(const function<bool(const T&)>& criterio) {
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
bool ListaEnlazada<T>::estaVacia() const { return cabeza == nullptr; }

template <typename T>
void ListaEnlazada<T>::porCada(const function<void(const T&)>& accion) const {
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