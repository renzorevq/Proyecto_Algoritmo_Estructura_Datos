#pragma once
#include <string>
#include "Usuario.h"

using namespace std;


class GrafoCanciones {
private:
    string nodos[MAX_GRAFO];
    bool matrizAdy[MAX_GRAFO][MAX_GRAFO];
    int total;
    int buscarIndice(const string& nombre);
    int posX[MAX_GRAFO];
    int posY[MAX_GRAFO];

public:
    GrafoCanciones();
    bool agregarCancion(const string& nombre);
    bool agregarConexion(const string& a, const string& b);
    void mostrarGrafoVisual();
    void interactuar(Usuario& usuario); 
};
