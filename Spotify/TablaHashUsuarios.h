#pragma once
#include <string>
#include "Usuario.h"
#include "Nodo.h"  // Usa el Nodo<T> que ya tienes

const int HASH_SIZE = 10;

class TablaHashUsuarios {
private:
    Nodo<Usuario>* tabla[HASH_SIZE];
    int hash(const string& correo);

public:
    TablaHashUsuarios();
    void insertar(const Usuario& u);
    Usuario* buscar(const string& correo);
    bool eliminar(const string& correo);
    void mostrar();
};
