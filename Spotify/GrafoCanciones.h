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
public:
    GrafoCanciones();
    bool agregarCancion(const string& nombre);
    bool agregarConexion(const string& a, const string& b);
    void mostrarGrafo();
    void interactuar(Usuario& usuario); 
};
