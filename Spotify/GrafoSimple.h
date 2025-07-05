#pragma once
#include "ListaAdyacencia.h"
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_VERTICES = 20;
const int MAX_NOMBRE = 50;

class GrafoSimple {
private:
    char vertices[MAX_VERTICES][MAX_NOMBRE]; // nombres de usuarios
    ListaAdyacencia<char*> adyacencias[MAX_VERTICES];
    int totalVertices;

    int buscarIndice(const char* nombre) const {
        for (int i = 0; i < totalVertices; ++i)
            if (strcmp(vertices[i], nombre) == 0)
                return i;
        return -1;
    }

public:
    GrafoSimple() : totalVertices(0) {}

    void agregarVertice(const char* nombre) {
        if (buscarIndice(nombre) != -1 || totalVertices >= MAX_VERTICES)
            return;
        strncpy(vertices[totalVertices], nombre, MAX_NOMBRE);
        ++totalVertices;
    }

    void agregarArista(const char* origen, const char* destino) {
        agregarVertice(origen);
        agregarVertice(destino);

        int i = buscarIndice(origen);
        int j = buscarIndice(destino);
        if (i == -1 || j == -1) return;

        adyacencias[i].agregarAdyacente(vertices[j]);
        adyacencias[j].agregarAdyacente(vertices[i]); // no dirigido
    }

    void mostrarGrafo() const {
        for (int i = 0; i < totalVertices; ++i) {
            cout << vertices[i];
            adyacencias[i].mostrar();
            cout << endl;
        }
    }
};
